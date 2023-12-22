//#include "LocationConfig.hpp"
//#include "ConfigInfo.hpp"

//LocationConfig::LocationConfig() : ConfigInfo() {}

//LocationConfig::LocationConfig(const size_t& port, const std::string& serverName,
//                               const size_t& clientMaxBodySize,
//                               const std::vector<std::string>& errorPage,
//                               const std::vector<std::string>& indexFile,
//                               const std::string& rootDir,
//                               bool autoIndex,
//                               const std::vector<std::string>& returnDirective)
//    : ConfigInfo(port, serverName, clientMaxBodySize, errorPage, indexFile,
//                rootDir, autoIndex)
//    , _return(returnDirective)
//{
//}

//LocationConfig::LocationConfig(const LocationConfig& lconfig)
//    : ConfigInfo(lconfig)
//    , _return(lconfig._return)
//{
//}

//LocationConfig::~LocationConfig() {}

//LocationConfig& LocationConfig::operator=(const LocationConfig& lconfig) {
//    if (this == &lconfig)
//        return *this;
//    ConfigInfo::operator=(lconfig);
//    _return = lconfig._return;
//    return *this;
//}

//const std::vector<std::string>& LocationConfig::getReturnDirective() const {
//    return _return;
//}
