#include "ServerConfig.hpp"
#include "ConfigInfo.hpp"
#include <cstddef>
#include <string>

ServerConfig::ServerConfig() : ConfigInfo() {}

ServerConfig::ServerConfig(const size_t& port, const std::set<std::string>& name,
                    const size_t& size, const std::set<std::string>& indx,
                    const std::set<std::string>& root_dir,
                    const std::map<size_t, std::string>& error_page,
                    const std::map<size_t, std::string>& return_page,
                    const std::set<std::string>& methods,
                    bool auto_index)
    : ConfigInfo(port, name, size, indx, root_dir, error_page, return_page,
                methods, auto_index)
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

void    ServerConfig::addLocation(LocationConfig lconf) {
    if (lconf.index().empty())
        lconf.set_index(_index);
    if (lconf.allow_methods().empty())
        lconf.set_allow_methods(_allow_methods);
    _locations.push_back(lconf);
}

void    ServerConfig::display() const {
    ConfigInfo::display();
    std::cout << "----> Location Block\n";
    for (size_t i = 0; i < _locations.size(); ++i) {
        std::cout << "path:";
        for (std::set<std::string>::const_iterator it = _locations[i].getPaths().begin();
                it != _locations[i].getPaths().end(); ++it)
            std::cout << " " << *it;
        std::cout << '\n';
        _locations[i].display();
    }
    std::cout << "--------------------\n";
}
