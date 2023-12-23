#include "ConfigInfo.hpp"

ConfigInfo::ConfigInfo() {}

ConfigInfo::ConfigInfo(const size_t& port, const std::set<std::string>& name,
                    const size_t& size, const std::set<std::string>& indx,
                    const std::set<std::string>& root_dir,
                    const std::map<size_t, std::string>& error_page,
                    const std::map<size_t, std::string>& return_page,
                    bool auto_index)
    : _port(port)
    , _server_name(name)
    , _client_max_body_size(size)
    , _index(indx)
    , _root(root_dir)
    , _error_page(error_page)
    , _return(return_page)
    , _autoindex(auto_index)
{
}

ConfigInfo::ConfigInfo(const ConfigInfo& conf)
    : _port(conf._port)
    , _server_name(conf._server_name)
    , _client_max_body_size(conf._client_max_body_size)
    , _index(conf._index)
    , _root(conf._root)
    , _error_page(conf._error_page)
    , _return(conf._return)
    , _autoindex(conf._autoindex)
{
}

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
    _autoindex = conf._autoindex;
    return *this;
}

const size_t&   ConfigInfo::port_number() const { return _port; }

const std::set<std::string>&    ConfigInfo::server_name() const {
    return _server_name;
}

const size_t&   ConfigInfo::client_max_body_size() const {
    return _client_max_body_size;
}

const std::set<std::string>&    ConfigInfo::index() const { return _index; }

const std::set<std::string>&    ConfigInfo::root() const { return _root; }

const std::map<size_t, std::string>&    ConfigInfo::error_page() const {
    return _error_page;
}

const std::map<size_t, std::string>&    ConfigInfo::return_page() const {
    return _return;
}

const bool& ConfigInfo::autoindex() const { return _autoindex; }

void    ConfigInfo::set_port_number(const size_t& port) {
    _port = port;
}

void    ConfigInfo::set_server_name(const std::set<std::string>& name) {
    _server_name = name;
}

void    ConfigInfo::set_client_max_body_size(const size_t& size) {
    _client_max_body_size = size;
}

void    ConfigInfo::set_index(const std::set<std::string>& indx) {
    _index = indx;
}

void    ConfigInfo::set_root(const std::set<std::string>& root_dir) {
    _root = root_dir;
}

void    ConfigInfo::set_error_page(const std::map<size_t, std::string>& errpage)
{
    _error_page = errpage;
}

void    ConfigInfo::set_return(const std::map<size_t, std::string>& return_page)
{
    _return = return_page;
}

void    ConfigInfo::set_autoindex(bool auto_index) {
    _autoindex = auto_index;
}
