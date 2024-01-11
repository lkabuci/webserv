#pragma once

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "../config/ServerConfig.hpp"

class Server {
  public:
    Server(const ServerConfig& svconf);
    Server(const Server& server);
    ~Server();

    Server& operator=(const Server& server);

    void          setServer(const ServerConfig& svconf);
    ServerConfig& getServerConfig();
    const int&    getSocket() const;

    const std::string&           ip() const;
    const std::string&           port() const;
    const std::set<std::string>& server_name() const;
    const size_t&                client_max_body_size() const;
    const std::set<std::string>& index() const;
    const std::set<std::string>& root() const;

    const std::map<size_t, std::string>& error_page() const;
    const std::map<size_t, std::string>& return_page() const;
    const std::set<std::string>&         allow_methods() const;
    const bool&                          autoindex() const;

  private:
    ServerConfig _svconf;
    int          _sockfd;
};

#endif
