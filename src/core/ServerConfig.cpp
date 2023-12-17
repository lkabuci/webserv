#include "HttpConfig.hpp"

ServerConfig::ServerConfig() {}

ServerConfig::ServerConfig(const LocationConfig& lconf, const size_t& port,
                        const std::string& domainName,
                        const std::string& rootDir,
                        const std::vector<std::string>& indexFiles,
                        const std::map<size_t, std::string>& errorPages)
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
