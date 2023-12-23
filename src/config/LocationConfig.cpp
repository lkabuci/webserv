#include "LocationConfig.hpp"

LocationConfig::LocationConfig() : ConfigInfo() {}

LocationConfig::LocationConfig(const size_t& port,
                    const std::set<std::string>& name,
                    const size_t& size, const std::set<std::string>& indx,
                    const std::set<std::string>& root_dir,
                    const std::map<size_t, std::string>& error_page,
                    const std::map<size_t, std::string>& return_page,
                    bool auto_index)
    : ConfigInfo(port, name, size, indx, root_dir, error_page, return_page,
                auto_index)
{
}

LocationConfig::LocationConfig(const LocationConfig& svconf) : ConfigInfo(svconf) {}

LocationConfig::~LocationConfig() {}

LocationConfig&   LocationConfig::operator=(const LocationConfig& svconf) {
    if (this == &svconf)
        return *this;
    ConfigInfo::operator=(svconf);
    return *this;
}
