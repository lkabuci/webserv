#include "GETRequestStrategy.hpp"
#include "../http/Request.hpp"
#include "../utils/MIMEType.hpp"
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <regex.h>
#include <sstream>
#include <sys/stat.h>

GetRequestStrategy::GetRequestStrategy(ClientEventHandler* pHandler)
    : _pHandler(pHandler) {}

GetRequestStrategy::~GetRequestStrategy() {}

// Returns true if the given location matches the URI
bool GetRequestStrategy::matchesLocation(const LocationConfig& loc,
                                         const std::string&    uri) const {
    const std::set<std::string>& paths = loc.getPaths();

    // Regex location: paths set contains "~"
    if (paths.find("~") != paths.end()) {
        for (std::set<std::string>::const_iterator it = paths.begin();
             it != paths.end(); ++it) {
            if (*it == "~")
                continue;
            regex_t re;
            if (regcomp(&re, it->c_str(), REG_EXTENDED | REG_NOSUB) == 0) {
                int match = regexec(&re, uri.c_str(), 0, NULL, 0);
                regfree(&re);
                if (match == 0)
                    return true;
            }
        }
        return false;
    }

    // Prefix match
    for (std::set<std::string>::const_iterator it = paths.begin();
         it != paths.end(); ++it) {
        const std::string& path = *it;
        if (uri == path)
            return true;
        if (uri.size() > path.size() &&
            uri.substr(0, path.size()) == path &&
            (path[path.size() - 1] == '/' || uri[path.size()] == '/'))
            return true;
    }
    return false;
}

// Returns the best matching LocationConfig for the URI, or NULL
const LocationConfig*
GetRequestStrategy::findBestLocation(const ServerConfig& config,
                                     const std::string&  uri) const {
    const std::vector<LocationConfig>& locations = config.getLocations();
    const LocationConfig*              best = NULL;
    size_t                             bestLen = 0;

    for (size_t i = 0; i < locations.size(); i++) {
        const std::set<std::string>& paths = locations[i].getPaths();

        // Regex locations
        if (paths.find("~") != paths.end()) {
            if (matchesLocation(locations[i], uri) && best == NULL)
                best = &locations[i];
            continue;
        }

        // Prefix: longest match wins
        for (std::set<std::string>::const_iterator it = paths.begin();
             it != paths.end(); ++it) {
            const std::string& path = *it;
            bool prefixMatch =
                (uri == path) ||
                (uri.size() > path.size() &&
                 uri.substr(0, path.size()) == path &&
                 (path[path.size() - 1] == '/' || uri[path.size()] == '/'));
            if (prefixMatch && path.size() > bestLen) {
                bestLen = path.size();
                best    = &locations[i];
            }
        }
    }
    return best;
}

void GetRequestStrategy::serveFile(const std::string& path) {
    std::ifstream file(path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        _pHandler->sendResponse(403, "text/plain", "Forbidden");
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

    // Determine MIME type from extension
    MIMEType    mime;
    std::string extension;
    size_t      dotPos = path.rfind('.');
    if (dotPos != std::string::npos && dotPos + 1 < path.size())
        extension = path.substr(dotPos + 1);
    std::string contentType = mime.getMimeTypeForExtension(extension);

    _pHandler->sendResponse(200, contentType, content);
}

void GetRequestStrategy::serveDirectory(const std::string& dirPath,
                                        const std::string& uri) {
    DIR* dir = opendir(dirPath.c_str());
    if (!dir) {
        _pHandler->sendResponse(403, "text/plain", "Forbidden");
        return;
    }

    std::ostringstream html;
    html << "<!DOCTYPE html>\n<html>\n<head><title>Index of " << uri
         << "</title></head>\n<body>\n<h1>Index of " << uri
         << "</h1>\n<hr>\n<pre>\n";

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string name = entry->d_name;
        if (name == ".")
            continue;

        std::string href = uri;
        if (href.empty() || href[href.size() - 1] != '/')
            href += '/';

        if (name == "..") {
            // Parent directory link
            std::string parent = uri;
            if (!parent.empty() && parent[parent.size() - 1] == '/')
                parent.erase(parent.size() - 1);
            size_t lastSlash = parent.rfind('/');
            if (lastSlash != std::string::npos)
                parent = parent.substr(0, lastSlash + 1);
            else
                parent = "/";
            html << "<a href=\"" << parent << "\">" << name << "/</a>\n";
        } else {
            html << "<a href=\"" << href << name << "\">" << name << "</a>\n";
        }
    }
    closedir(dir);

    html << "</pre>\n<hr>\n</body>\n</html>\n";
    _pHandler->sendResponse(200, "text/html", html.str());
}

void GetRequestStrategy::serveErrorPage(int code, const ServerConfig& config) {
    // Try custom error page from config
    const std::map<size_t, std::string>& errorPages = config.error_page();
    std::map<size_t, std::string>::const_iterator it =
        errorPages.find(static_cast<size_t>(code));

    if (it != errorPages.end()) {
        std::string root;
        if (!config.root().empty())
            root = *config.root().begin();
        std::string errorPath = root + it->second;

        struct stat st;
        if (stat(errorPath.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
            std::ifstream file(errorPath.c_str());
            if (file.is_open()) {
                std::string content((std::istreambuf_iterator<char>(file)),
                                    std::istreambuf_iterator<char>());
                file.close();
                _pHandler->sendResponse(code, "text/html", content);
                return;
            }
        }
    }

    // Default inline error page
    std::string msg;
    switch (code) {
    case 403: msg = "Forbidden"; break;
    case 404: msg = "Not Found"; break;
    case 405: msg = "Method Not Allowed"; break;
    default:  msg = "Error"; break;
    }

    std::ostringstream html;
    html << "<!DOCTYPE html>\n<html>\n<head><title>" << code << " " << msg
         << "</title></head>\n<body>\n<h1>" << code << " " << msg
         << "</h1>\n</body>\n</html>\n";
    _pHandler->sendResponse(code, "text/html", html.str());
}

void GetRequestStrategy::handleRequest(const Request& request) {
    // Strip query string from URI
    std::string uri     = request.getUri();
    size_t      qmark   = uri.find('?');
    if (qmark != std::string::npos)
        uri = uri.substr(0, qmark);

    const ServerConfig& config = _pHandler->getServer().getServerConfig();

    // Find best matching location block
    const LocationConfig* loc = findBestLocation(config, uri);

    // Handle redirect (return directive)
    if (loc && !loc->return_page().empty()) {
        const std::map<size_t, std::string>& ret = loc->return_page();
        std::map<size_t, std::string>::const_iterator it = ret.begin();
        _pHandler->sendRedirectResponse(static_cast<int>(it->first),
                                        it->second);
        return;
    }

    // Check if GET is an allowed method for this location
    const std::set<std::string>* allowed = NULL;
    if (loc && !loc->allow_methods().empty())
        allowed = &loc->allow_methods();
    else if (!config.allow_methods().empty())
        allowed = &config.allow_methods();

    if (allowed && allowed->find("GET") == allowed->end()) {
        serveErrorPage(405, config);
        return;
    }

    // Resolve root directory
    std::string root;
    if (loc && !loc->root().empty())
        root = *loc->root().begin();
    else if (!config.root().empty())
        root = *config.root().begin();

    // Build the file system path.
    // When a location has its own root, use alias semantics:
    // strip the location prefix from the URI before appending to root.
    std::string filepath;
    if (loc && !loc->root().empty()) {
        // Find the longest prefix matched by this location
        std::string                  locPrefix;
        const std::set<std::string>& paths = loc->getPaths();
        for (std::set<std::string>::const_iterator it = paths.begin();
             it != paths.end(); ++it) {
            if (*it == "~")
                continue;
            if (uri.size() >= it->size() &&
                uri.substr(0, it->size()) == *it &&
                it->size() > locPrefix.size())
                locPrefix = *it;
        }
        std::string relUri = uri.substr(locPrefix.size());
        if (relUri.empty())
            relUri = "/";
        filepath = root + relUri;
    } else {
        filepath = root + uri;
    }

    struct stat st;
    if (stat(filepath.c_str(), &st) != 0) {
        serveErrorPage(404, config);
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        // Redirect to canonical directory URL (trailing slash)
        if (uri.empty() || uri[uri.size() - 1] != '/') {
            _pHandler->sendRedirectResponse(301, uri + "/");
            return;
        }

        // Try index files
        const std::set<std::string>* indexFiles = NULL;
        if (loc && !loc->index().empty())
            indexFiles = &loc->index();
        else if (!config.index().empty())
            indexFiles = &config.index();

        if (indexFiles) {
            for (std::set<std::string>::const_iterator it = indexFiles->begin();
                 it != indexFiles->end(); ++it) {
                std::string indexPath = filepath + *it;
                struct stat ist;
                if (stat(indexPath.c_str(), &ist) == 0 && S_ISREG(ist.st_mode)) {
                    serveFile(indexPath);
                    return;
                }
            }
        }

        // Try autoindex
        bool autoindex = loc ? loc->autoindex() : config.autoindex();
        if (autoindex) {
            serveDirectory(filepath, uri);
            return;
        }

        serveErrorPage(403, config);
    } else {
        serveFile(filepath);
    }
}
