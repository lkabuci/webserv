//#include "ServerConfig.hpp"
//#include "LocationConfig.hpp"

//ServerConfig::ServerConfig() : ConfigInfo() {}

//ServerConfig::ServerConfig(const std::vector<LocationConfig>& locations,
//                            const size_t& port, const std::string& serverName,
//                            const size_t& clientMaxBodySize,
//                            const std::vector<std::string>& errorPage,
//                            const std::vector<std::string>& indexFile,
//                            const std::string& rootDir,
//                            bool autoIndex)
//    : ConfigInfo(port, serverName, clientMaxBodySize, errorPage, indexFile,
//                rootDir, autoIndex)
//    , _location(locations)
//{
//}

//ServerConfig::ServerConfig(const ServerConfig& lconfig)
//    : ConfigInfo(lconfig)
//    , _location(lconfig._location)
//{
//}

//ServerConfig::~ServerConfig() {}

//ServerConfig& ServerConfig::operator=(const ServerConfig& lconfig) {
//    if (this == &lconfig)
//        return *this;
//    ConfigInfo::operator=(lconfig);
//    _location = lconfig._location;
//    return *this;
//}

//std::vector<LocationConfig>& ServerConfig::getLocations() {
//    return _location;
//}

//void    ServerConfig::addLocation(const LocationConfig& location) {
//    _location.push_back(location);
//}
