#include "ServerConfig.hpp"

ServerConfig::ServerConfig() : ConfigInfo() {}

ServerConfig::ServerConfig(const size_t& port, const std::set<std::string>& name,
                    const size_t& size, const std::set<std::string>& indx,
                    const std::set<std::string>& root_dir,
                    const std::map<size_t, std::string>& error_page,
                    const std::map<size_t, std::string>& return_page,
                    bool auto_index)
    : ConfigInfo(port, name, size, indx, root_dir, error_page, return_page,
                auto_index)
{
}

ServerConfig::ServerConfig(const ServerConfig& svconf)
    : ConfigInfo(svconf)
    , _locations(svconf._locations)
{
}

ServerConfig::~ServerConfig() {}

ServerConfig&   ServerConfig::operator=(const ServerConfig& svconf) {
    if (this == &svconf)
        return *this;
    ConfigInfo::operator=(svconf);
    _locations = svconf._locations;
    return *this;
}

std::vector<LocationConfig>&    ServerConfig::getLocations() {
    return _locations;
}

void    ServerConfig::addLocation(const LocationConfig& lconf) {
    _locations.push_back(lconf);
}
