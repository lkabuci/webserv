#include "LocationConfig.hpp"

LocationConfig::LocationConfig() : ConfigInfo() {}

LocationConfig::LocationConfig(
    const std::set<std::string>& paths, const size_t& port,
    const std::set<std::string>& name, const size_t& size,
    const std::set<std::string>& indx, const std::set<std::string>& root_dir,
    const std::map<size_t, std::string>& error_page,
    const std::map<size_t, std::string>& return_page,
    const std::set<std::string>& methods, bool auto_index)
    : ConfigInfo(port, name, size, indx, root_dir, error_page, return_page,
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

bool operator==(const LocationConfig& l1, const LocationConfig& l2) {
    return l1.port_number() == l2.port_number() &&
           l1.server_name() == l2.server_name() &&
           l1.client_max_body_size() == l2.client_max_body_size() &&
           l1.index() == l2.index() && l1.root() == l2.root() &&
           l1.error_page() == l2.error_page() &&
           l1.return_page() == l2.return_page() &&
           l1.allow_methods() == l2.allow_methods() &&
           l1.autoindex() == l2.autoindex() && l1.getPaths() == l2.getPaths();
}
