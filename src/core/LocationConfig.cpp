#include "HttpConfig.hpp"

LocationConfig::LocationConfig(const std::string& path) : _path(path) {}


LocationConfig::LocationConfig(const std::string& path, const size_t& port,
            const std::vector<std::string>& domainName,
            const std::string& rootDir,
            const std::vector<std::string>& indexFiles,
            const keyVector& errorPages)
    : HttpConfig(port, domainName, rootDir, indexFiles, errorPages)
    , _path(path)
{
}

LocationConfig::LocationConfig(const LocationConfig& lconf)
    : HttpConfig(lconf)
    , _path(lconf._path)
{
}

LocationConfig::~LocationConfig() {}

LocationConfig& LocationConfig::operator=(const LocationConfig& lconf) {
    if (this == &lconf)
        return *this;
    HttpConfig::operator=(lconf);
    _path = lconf._path;
    return *this;
}

void    LocationConfig::showClassName() const {
    std::cout << "Location Context:\n";
}

void    LocationConfig::addPath(const std::string& path) {
    _path = path;
}

const std::string&  LocationConfig::getPath() const { return _path; }
