#include "LocationConfig.hpp"

LocationConfig::LocationConfig() : ConfigInfo() {}

LocationConfig::LocationConfig(const std::set<std::string>& paths,
                               const std::string& ip, const std::string& port,
                               const std::set<std::string>&         name,
                               const size_t&                        size,
                               const std::set<std::string>&         indx,
                               const std::set<std::string>&         root_dir,
                               const std::map<size_t, std::string>& error_page,
                               const std::map<size_t, std::string>& return_page,
                               const std::set<std::string>&         methods,
                               bool                                 auto_index)
    : ConfigInfo(ip, port, name, size, indx, root_dir, error_page, return_page,
                 methods, auto_index),
      _paths(paths) {}

LocationConfig::LocationConfig(const LocationConfig& svconf)
    : ConfigInfo(svconf), _paths(svconf._paths) {}

LocationConfig::~LocationConfig() {}

LocationConfig& LocationConfig::operator=(const LocationConfig& lconf) {
    if (this == &lconf)
        return *this;
    ConfigInfo::operator=(lconf);
    _paths = lconf._paths;
    return *this;
}

const std::set<std::string>& LocationConfig::getPaths() const {
    return _paths;
}

void LocationConfig::addPath(const std::string& path) {
    _paths.insert(_paths.end(), path);
}

void LocationConfig::addPath(const std::vector<std::string>& paths) {
    _paths.insert(paths.begin(), paths.end());
}
