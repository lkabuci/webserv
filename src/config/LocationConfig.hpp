#ifndef __LOCATION_CONFIG_HPP__
#define __LOCATION_CONFIG_HPP__

#include "ConfigInfo.hpp"

class LocationConfig : public ConfigInfo {
public:
    LocationConfig();
    LocationConfig(const size_t& port, const std::set<std::string>& name,
                const size_t& size, const std::set<std::string>& indx,
                const std::set<std::string>& root_dir,
                const std::map<size_t, std::string>& error_page,
                const std::map<size_t, std::string>& return_page,
                bool auto_index);
    LocationConfig(const LocationConfig& svconfig);
    virtual ~LocationConfig();

    LocationConfig&   operator=(const LocationConfig& svconfig);
};

#endif
