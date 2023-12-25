#include "ConfigInfo.hpp"

ConfigInfo::ConfigInfo()
    : _port(8000), _client_max_body_size(100), _autoindex(false) {
    _server_name.insert("-");
}

ConfigInfo::ConfigInfo(const size_t& port, const std::set<std::string>& name,
                       const size_t& size, const std::set<std::string>& indx,
                       const std::set<std::string>&         root_dir,
                       const std::map<size_t, std::string>& error_page,
                       const std::map<size_t, std::string>& return_page,
                       const std::set<std::string>& methods, bool auto_index)
    : _port(port), _server_name(name), _client_max_body_size(size),
      _index(indx), _root(root_dir), _error_page(error_page),
      _return(return_page), _allow_methods(methods), _autoindex(auto_index) {}

ConfigInfo::ConfigInfo(const ConfigInfo& conf)
    : _port(conf._port), _server_name(conf._server_name),
      _client_max_body_size(conf._client_max_body_size), _index(conf._index),
      _root(conf._root), _error_page(conf._error_page), _return(conf._return),
      _allow_methods(conf._allow_methods), _autoindex(conf._autoindex) {}

ConfigInfo::~ConfigInfo() {}

ConfigInfo& ConfigInfo::operator=(const ConfigInfo& conf) {
    if (this == &conf)
        return *this;
    _port = conf._port;
    _server_name = conf._server_name;
    _client_max_body_size = conf._client_max_body_size;
    _index = conf._index;
    _root = conf._root;
    _error_page = conf._error_page;
    _return = conf._return;
    _allow_methods = conf._allow_methods;
    _autoindex = conf._autoindex;
    return *this;
}

const size_t& ConfigInfo::port_number() const {
    return _port;
}

const std::set<std::string>& ConfigInfo::server_name() const {
    return _server_name;
}

const size_t& ConfigInfo::client_max_body_size() const {
    return _client_max_body_size;
}

const std::set<std::string>& ConfigInfo::index() const {
    return _index;
}

const std::set<std::string>& ConfigInfo::root() const {
    return _root;
}

const std::map<size_t, std::string>& ConfigInfo::error_page() const {
    return _error_page;
}

const std::map<size_t, std::string>& ConfigInfo::return_page() const {
    return _return;
}

const std::set<std::string>& ConfigInfo::allow_methods() const {
    return _allow_methods;
}

const bool& ConfigInfo::autoindex() const {
    return _autoindex;
}

void ConfigInfo::set_port_number(const size_t& port) {
    _port = port;
}

void ConfigInfo::set_server_name(const std::set<std::string>& name) {
    _server_name = name;
}

void ConfigInfo::set_client_max_body_size(const size_t& size) {
    _client_max_body_size = size;
}

void ConfigInfo::set_index(const std::set<std::string>& indx) {
    _index.insert(indx.begin(), indx.end());
}

void ConfigInfo::set_root(const std::set<std::string>& root_dir) {
    _root.insert(root_dir.begin(), root_dir.end());
}

void ConfigInfo::set_error_page(const std::map<size_t, std::string>& errpage) {
    _error_page.insert(errpage.begin(), errpage.end());
}

void ConfigInfo::set_return(const std::map<size_t, std::string>& return_page) {
    _return.insert(return_page.begin(), return_page.end());
}

void ConfigInfo::set_allow_methods(const std::set<std::string>& methods) {
    _allow_methods.insert(methods.begin(), methods.end());
}

void ConfigInfo::set_autoindex(bool auto_index) {
    _autoindex = auto_index;
}

void ConfigInfo::display() const {
    std::cout << "port_number: " << _port << '\n';
    if (!_server_name.empty()) {
        std::cout << "server_name:";
        for (std::set<std::string>::const_iterator it = _server_name.begin();
             it != _server_name.end(); ++it)
            std::cout << " " << *it;
        std::cout << '\n';
    }
    std::cout << "client_max_body_size: " << _client_max_body_size << '\n';
    if (!_index.empty()) {
        std::cout << "index:";
        for (std::set<std::string>::const_iterator it = _index.begin();
             it != _index.end(); ++it)
            std::cout << " " << *it;
        std::cout << '\n';
    }
    if (!_root.empty()) {
        std::cout << "root:";
        for (std::set<std::string>::const_iterator it = _root.begin();
             it != _root.end(); ++it)
            std::cout << " " << *it;
        std::cout << '\n';
    }
    if (!_error_page.empty()) {
        std::cout << "error_page:\n";
        for (std::map<size_t, std::string>::const_iterator it =
                 _error_page.begin();
             it != _error_page.end(); ++it)
            std::cout << " " << it->first << " : " << it->second << '\n';
    }
    if (!_return.empty()) {
        std::cout << "return:\n";
        for (std::map<size_t, std::string>::const_iterator it = _return.begin();
             it != _return.end(); ++it)
            std::cout << " " << it->first << " : " << it->second << '\n';
    }
    if (!_allow_methods.empty()) {
        std::cout << "allow_methods:";
        for (std::set<std::string>::const_iterator it = _allow_methods.begin();
             it != _allow_methods.end(); ++it)
            std::cout << " " << *it;
        std::cout << '\n';
    }
    std::cout << "autoindex: " << _autoindex << '\n';
}
