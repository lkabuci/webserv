#pragma once

#ifndef __SERVER_CONFIG_HPP__
#define __SERVER_CONFIG_HPP__

#include "ConfigInfo.hpp"
#include "LocationConfig.hpp"

class ServerConfig : public ConfigInfo {
  public:
    ServerConfig();
    ServerConfig(const size_t& port, const std::set<std::string>& name,
                 const size_t& size, const std::set<std::string>& index,
                 const std::set<std::string>&         root_dir,
                 const std::map<size_t, std::string>& error_page,
                 const std::map<size_t, std::string>& return_page,
                 const std::set<std::string>& methods, bool auto_index);
    ServerConfig(const ServerConfig& svconfig);
    virtual ~ServerConfig();

    ServerConfig& operator=(const ServerConfig& svconfig);

    void                         addLocation(LocationConfig lconf);
    std::vector<LocationConfig>& getLocations();

    virtual void display() const;

    friend bool operator==(const ServerConfig& s1, const ServerConfig& s2);

  private:
    std::vector<LocationConfig> _locations;
};

#endif
