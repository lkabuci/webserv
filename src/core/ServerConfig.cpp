#include "HttpConfig.hpp"

ServerConfig::ServerConfig() {}

ServerConfig::ServerConfig(const std::vector<LocationConfig>& lconf,
                        const size_t& port,
                        const std::vector<std::string>& domainName,
                        const std::string& rootDir,
                        const std::vector<std::string>& indexFiles,
                        const keyVector& errorPages)
    : HttpConfig(port, domainName, rootDir, indexFiles, errorPages)
    , _locationConf(lconf)
{
}

ServerConfig::ServerConfig(const ServerConfig& svconf)
    : HttpConfig(svconf)
    , _locationConf(svconf._locationConf)
{
}

ServerConfig::~ServerConfig() {}

ServerConfig&   ServerConfig::operator=(const ServerConfig& svconf) {
    if (this == &svconf)
        return *this;
    _locationConf = svconf._locationConf;
    HttpConfig::operator=(svconf);
    return *this;
}

void   ServerConfig::addLocation(const LocationConfig& lconf) {
    _locationConf.push_back(lconf);
}

std::vector<LocationConfig>&   ServerConfig::getLocations() {
    return _locationConf;
}

void    ServerConfig::addLocationPath(const std::string& path, size_t pos) {
    _locationConf[pos].addPath(path);
}

const std::string&  ServerConfig::getLocationPath(size_t pos) const {
    return _locationConf[pos].getPath();
}

void    ServerConfig::showClassName() const {
    for (size_t i = 0; i < _locationConf.size(); ++i)
        _locationConf[i].display();
    std::cout << "Server Context:\n";
}
