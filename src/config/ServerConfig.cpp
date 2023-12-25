#include "ServerConfig.hpp"
#include "ConfigInfo.hpp"

ServerConfig::ServerConfig() : ConfigInfo() {}

ServerConfig::ServerConfig(
    const size_t& port, const std::set<std::string>& name, const size_t& size,
    const std::set<std::string>& indx, const std::set<std::string>& root_dir,
    const std::map<size_t, std::string>& error_page,
    const std::map<size_t, std::string>& return_page,
    const std::set<std::string>& methods, bool auto_index)
    : ConfigInfo(port, name, size, indx, root_dir, error_page, return_page,
                 methods, auto_index) {}

ServerConfig::ServerConfig(const ServerConfig& svconf)
    : ConfigInfo(svconf), _locations(svconf._locations) {}

ServerConfig::~ServerConfig() {}

ServerConfig& ServerConfig::operator=(const ServerConfig& svconf) {
    if (this == &svconf)
        return *this;
    ConfigInfo::operator=(svconf);
    _locations = svconf._locations;
    return *this;
}

std::vector<LocationConfig>& ServerConfig::getLocations() { return _locations; }

void ServerConfig::addLocation(LocationConfig lconf) {
    if (lconf.index().empty())
        lconf.set_index(_index);
    if (lconf.allow_methods().empty())
        lconf.set_allow_methods(_allow_methods);
    _locations.push_back(lconf);
}

void ServerConfig::display() const {
    ConfigInfo::display();
    std::cout << "----> Location Block\n";
    for (size_t i = 0; i < _locations.size(); ++i) {
        std::cout << "path:";
        for (std::set<std::string>::const_iterator it =
                 _locations[i].getPaths().begin();
             it != _locations[i].getPaths().end(); ++it)
            std::cout << " " << *it;
        std::cout << '\n';
        _locations[i].display();
    }
    std::cout << "--------------------\n";
}

bool operator==(const ServerConfig& s1, const ServerConfig& s2) {
    return s1._port == s2._port && s1._server_name == s2._server_name &&
           s1._client_max_body_size == s2._client_max_body_size &&
           s1._index == s2._index && s1._root == s2._root &&
           s1._error_page == s2._error_page && s1._return == s2._return &&
           s1._allow_methods == s2._allow_methods &&
           s1._autoindex == s2._autoindex && s1._locations == s2._locations;
}
