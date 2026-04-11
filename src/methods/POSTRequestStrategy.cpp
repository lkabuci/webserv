#include "POSTRequestStrategy.hpp"
#include "../http/Request.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>

PostRequestStrategy::PostRequestStrategy(ClientEventHandler* pHandler)
    : _pHandler(pHandler) {}

PostRequestStrategy::~PostRequestStrategy() {}

// Saves an uploaded body to a file in uploadDir.
// If content-type is multipart/form-data, extracts the file part.
// Returns true on success.
bool PostRequestStrategy::saveUpload(const std::string& body,
                                     const std::string& contentType,
                                     const std::string& uploadDir) {
    // Generate a timestamped filename
    std::ostringstream oss;
    oss << uploadDir;
    if (!uploadDir.empty() && uploadDir[uploadDir.size() - 1] != '/')
        oss << '/';

    std::string fileContent = body;
    std::string filename;

    // Parse multipart/form-data
    size_t boundaryPos = contentType.find("boundary=");
    if (boundaryPos != std::string::npos) {
        std::string boundary = "--" + contentType.substr(boundaryPos + 9);
        // Strip surrounding whitespace/quotes from boundary
        size_t start = boundary.find_first_not_of(" \t\"");
        size_t end = boundary.find_last_not_of(" \t\"");
        if (start != std::string::npos)
            boundary = boundary.substr(start, end - start + 1);

        // Find first boundary
        size_t partStart = body.find(boundary);
        if (partStart != std::string::npos) {
            partStart += boundary.size();
            // Skip CRLF after boundary line
            if (body.size() > partStart + 1 && body[partStart] == '\r' &&
                body[partStart + 1] == '\n')
                partStart += 2;
            else if (body.size() > partStart && body[partStart] == '\n')
                partStart += 1;

            // Read part headers
            size_t partHeaderEnd = body.find("\r\n\r\n", partStart);
            if (partHeaderEnd == std::string::npos)
                partHeaderEnd = body.find("\n\n", partStart);

            if (partHeaderEnd != std::string::npos) {
                std::string partHeaders =
                    body.substr(partStart, partHeaderEnd - partStart);

                // Try to extract filename from Content-Disposition
                size_t fnPos = partHeaders.find("filename=\"");
                if (fnPos != std::string::npos) {
                    fnPos += 10;
                    size_t fnEnd = partHeaders.find('"', fnPos);
                    if (fnEnd != std::string::npos)
                        filename = partHeaders.substr(fnPos, fnEnd - fnPos);
                }

                // Part body starts after part headers
                size_t bodyStart = partHeaderEnd + 4; // skip \r\n\r\n
                if (body[partHeaderEnd] == '\n')
                    bodyStart = partHeaderEnd + 2;

                // Find end boundary
                size_t bodyEnd = body.find(boundary, bodyStart);
                if (bodyEnd != std::string::npos) {
                    // Remove trailing CRLF before boundary
                    if (bodyEnd >= 2 && body[bodyEnd - 2] == '\r' &&
                        body[bodyEnd - 1] == '\n')
                        bodyEnd -= 2;
                    else if (bodyEnd >= 1 && body[bodyEnd - 1] == '\n')
                        bodyEnd -= 1;
                    fileContent = body.substr(bodyStart, bodyEnd - bodyStart);
                } else {
                    fileContent = body.substr(bodyStart);
                }
            }
        }
    }

    if (filename.empty()) {
        // Generate a unique name based on timestamp
        std::ostringstream ts;
        ts << static_cast<long>(std::time(NULL));
        filename = "upload_" + ts.str();
    }

    std::string   filepath = oss.str() + filename;
    std::ofstream out(filepath.c_str(), std::ios::binary | std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "POST: cannot open file for writing: " << filepath << " ("
                  << strerror(errno) << ")" << std::endl;
        return false;
    }
    out.write(fileContent.c_str(),
              static_cast<std::streamsize>(fileContent.size()));
    out.close();
    return true;
}

void PostRequestStrategy::handleRequest(const Request& request) {
    const ServerConfig& config = _pHandler->getServer().getServerConfig();

    // Determine upload directory from location or server root
    std::string uri = request.getUri();
    size_t      q = uri.find('?');
    if (q != std::string::npos)
        uri = uri.substr(0, q);

    // Find matching location
    const std::vector<LocationConfig>& locations = config.getLocations();
    const LocationConfig*              loc = NULL;
    size_t                             bestLen = 0;
    for (size_t i = 0; i < locations.size(); i++) {
        const std::set<std::string>& paths = locations[i].getPaths();
        for (std::set<std::string>::const_iterator it = paths.begin();
             it != paths.end(); ++it) {
            const std::string& path = *it;
            if (path == "~")
                continue;
            bool match =
                (uri == path) ||
                (uri.size() > path.size() &&
                 uri.substr(0, path.size()) == path &&
                 (path[path.size() - 1] == '/' || uri[path.size()] == '/'));
            if (match && path.size() > bestLen) {
                bestLen = path.size();
                loc = &locations[i];
            }
        }
    }

    // Check method allowed
    const std::set<std::string>* allowed = NULL;
    if (loc && !loc->allow_methods().empty())
        allowed = &loc->allow_methods();
    else if (!config.allow_methods().empty())
        allowed = &config.allow_methods();

    if (allowed && allowed->find("POST") == allowed->end()) {
        _pHandler->sendResponse(405, "text/plain", "Method Not Allowed");
        return;
    }

    // Check body size
    const std::string& body = request.getBody();
    if (config.client_max_body_size() > 0 &&
        body.size() > config.client_max_body_size() * 1024 * 1024) {
        _pHandler->sendResponse(413, "text/plain", "Request Entity Too Large");
        return;
    }

    // Determine upload directory (alias semantics: strip location prefix)
    std::string uploadDir;
    if (loc && !loc->root().empty()) {
        uploadDir = *loc->root().begin();
    } else if (!config.root().empty()) {
        uploadDir = *config.root().begin();
    }

    // Get content-type header
    std::string contentType =
        request.getHeaderValue(request.getHeaders(), "Content-Type");

    // Ensure upload directory exists
    struct stat st;
    if (stat(uploadDir.c_str(), &st) != 0 || !S_ISDIR(st.st_mode)) {
        _pHandler->sendResponse(500, "text/plain",
                                "Upload directory not found");
        return;
    }

    if (!saveUpload(body, contentType, uploadDir)) {
        _pHandler->sendResponse(500, "text/plain", "Failed to save upload");
        return;
    }

    _pHandler->sendResponse(201, "text/plain", "Created");
}
