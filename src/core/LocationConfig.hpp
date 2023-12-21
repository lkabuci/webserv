#ifndef __LOCATION_CONFIG_HPP__
#define __LOCATION_CONFIG_HPP__

#include "ConfigInfo.hpp"

class LocationConfig : public ConfigInfo {
public:
    LocationConfig();
    LocationConfig(const size_t& port, const std::string& host,
                 const size_t& clientMaxBodySize,
                 const std::vector<std::string>& errorPage,
                 const std::string& indexFile, const std::string& rootDir,
                 bool autoIndex,
                 const std::vector<std::string>& returnDirective);
    LocationConfig(const LocationConfig& lconfig);
    virtual ~LocationConfig();

    LocationConfig&   operator=(const LocationConfig& lconfig);

private:
    std::vector<std::string>    _return;
};


#endif
