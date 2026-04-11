#include "DELETERequestStrategy.hpp"
#include "../http/Request.hpp"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

DELETERequestStrategy::DELETERequestStrategy(ClientEventHandler* pHandler)
    : _pHandler(pHandler) {}

DELETERequestStrategy::~DELETERequestStrategy() {}

void DELETERequestStrategy::handleRequest(const Request& request) {
    const ServerConfig& config = _pHandler->getServer().getServerConfig();

    std::string uri = request.getUri();
    size_t      q = uri.find('?');
    if (q != std::string::npos)
        uri = uri.substr(0, q);

    // Find best matching location (simple prefix match)
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

    if (allowed && allowed->find("DELETE") == allowed->end()) {
        _pHandler->sendResponse(405, "text/plain", "Method Not Allowed");
        return;
    }

    // Resolve file path (alias semantics: strip location prefix when location
    // has root)
    std::string root;
    if (loc && !loc->root().empty())
        root = *loc->root().begin();
    else if (!config.root().empty())
        root = *config.root().begin();

    std::string filepath;
    if (loc && !loc->root().empty()) {
        std::string                  locPrefix;
        const std::set<std::string>& paths = loc->getPaths();
        for (std::set<std::string>::const_iterator it = paths.begin();
             it != paths.end(); ++it) {
            if (*it == "~")
                continue;
            if (uri.size() >= it->size() && uri.substr(0, it->size()) == *it &&
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
        _pHandler->sendResponse(404, "text/plain", "Not Found");
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        _pHandler->sendResponse(403, "text/plain",
                                "Forbidden: cannot delete directory");
        return;
    }

    if (std::remove(filepath.c_str()) != 0) {
        if (errno == EACCES || errno == EPERM)
            _pHandler->sendResponse(403, "text/plain", "Forbidden");
        else
            _pHandler->sendResponse(500, "text/plain", "Internal Server Error");
        return;
    }

    _pHandler->sendResponse(200, "text/plain", "Deleted");
}
