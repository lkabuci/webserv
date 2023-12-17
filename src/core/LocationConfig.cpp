#include "HttpConfig.hpp"

LocationConfig::LocationConfig() {}


LocationConfig::LocationConfig(const size_t& port, const std::string& domainName,
            const std::string& rootDir,
            const std::vector<std::string>& indexFiles,
            const std::map<size_t, std::string>& errorPages)
    : HttpConfig(port, domainName, rootDir, indexFiles, errorPages)
{
}

LocationConfig::LocationConfig(const LocationConfig& lconf) : HttpConfig(lconf) {}

LocationConfig::~LocationConfig() {}

LocationConfig& LocationConfig::operator=(const LocationConfig& lconf) {
    if (this == &lconf)
        return *this;
    HttpConfig::operator=(lconf);
    return *this;
}
