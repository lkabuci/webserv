//#ifndef __SERVER_CONFIG_HPP__
//#define __SERVER_CONFIG_HPP__

//#include "ConfigInfo.hpp"
//#include "LocationConfig.hpp"

//class ServerConfig : public ConfigInfo {
//public:
//    ServerConfig();
//    ServerConfig(const std::vector<LocationConfig>& locations,
//                const size_t& port, const std::string& serverName,
//                const size_t& clientMaxBodySize,
//                const std::vector<std::string>& errorPage,
//                const std::vector<std::string>& indexFile,
//                const std::string& rootDir,
//                bool autoIndex);
//    ServerConfig(const ServerConfig& svconfig);
//    virtual ~ServerConfig();

//    ServerConfig&   operator=(const ServerConfig& svconfig);

//    std::vector<LocationConfig>& getLocations();

//    void    addLocation(const LocationConfig& location);

//private:
//    std::vector<LocationConfig> _location;
//};

//#endif
