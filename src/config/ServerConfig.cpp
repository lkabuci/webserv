#include "ServerConfig.hpp"
#include "ConfigInfo.hpp"

ServerConfig::ServerConfig() : ConfigInfo() {}

ServerConfig::ServerConfig(const std::string& ip, const std::string& port,
                           const std::set<std::string>&         name,
                           const size_t&                        size,
                           const std::set<std::string>&         indx,
                           const std::set<std::string>&         root_dir,
                           const std::map<size_t, std::string>& error_page,
                           const std::map<size_t, std::string>& return_page,
                           const std::set<std::string>&         methods,
                           bool                                 auto_index)
    : ConfigInfo(ip, port, name, size, indx, root_dir, error_page, return_page,
                 methods, auto_index) {}

ServerConfig::ServerConfig(const ServerConfig& svconf)
    : ConfigInfo(svconf), _locations(svconf._locations),
      _socketfd(svconf._socketfd) {}

ServerConfig::~ServerConfig() {}

ServerConfig& ServerConfig::operator=(const ServerConfig& svconf) {
    if (this == &svconf)
        return *this;
    ConfigInfo::operator=(svconf);
    _locations = svconf._locations;
    _socketfd = svconf._socketfd;
    return *this;
}

std::vector<LocationConfig>& ServerConfig::getLocations() {
    return _locations;
}

void ServerConfig::addLocation(LocationConfig lconf) {
    if (lconf.index().empty())
        lconf.set_index(_index);
    if (lconf.allow_methods().empty())
        lconf.set_allow_methods(_allow_methods);
    _locations.push_back(lconf);
}

const int& ServerConfig::getSocket() const {
    return _socketfd;
}

void ServerConfig::setSocket() {
    Socket sock(_ip.c_str(), _port.c_str());

    _socketfd = sock.getSocketfd();
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
