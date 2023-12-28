#pragma once

#ifndef __CONFIG_INFO_HPP__
#define __CONFIG_INFO_HPP__

#include "common.hpp"

class ConfigInfo {
  public:
    ConfigInfo();
    ConfigInfo(const size_t& port, const std::set<std::string>& name,
               const size_t& size, const std::set<std::string>& index,
               const std::set<std::string>&         root_dir,
               const std::map<size_t, std::string>& error_page,
               const std::map<size_t, std::string>& return_page,
               const std::set<std::string>& methods, bool auto_index);
    ConfigInfo(const ConfigInfo& conf);
    virtual ~ConfigInfo() = 0;

    ConfigInfo& operator=(const ConfigInfo& conf);

    const size_t&                        port_number() const;
    const std::set<std::string>&         server_name() const;
    const size_t&                        client_max_body_size() const;
    const std::set<std::string>&         index() const;
    const std::set<std::string>&         root() const;
    const std::map<size_t, std::string>& error_page() const;
    const std::map<size_t, std::string>& return_page() const;
    const std::set<std::string>&         allow_methods() const;
    const bool&                          autoindex() const;

    void set_port_number(const size_t& port);
    void set_server_name(const std::set<std::string>& name);
    void set_client_max_body_size(const size_t& size);
    void set_index(const std::set<std::string>& index);
    void set_root(const std::set<std::string>& root_dir);
    void set_error_page(const std::map<size_t, std::string>& errpage);
    void set_return(const std::map<size_t, std::string>& return_page);
    void set_allow_methods(const std::set<std::string>& methods);
    void set_autoindex(bool auto_index);

    virtual void display() const;

  protected:
    static std::vector<std::string> _methods;
    size_t                          _port;
    std::set<std::string>           _server_name;
    size_t                          _client_max_body_size;
    std::set<std::string>           _index;
    std::set<std::string>           _root;
    std::map<size_t, std::string>   _error_page;
    std::map<size_t, std::string>   _return;
    std::set<std::string>           _allow_methods;
    bool                            _autoindex;
};

#endif
