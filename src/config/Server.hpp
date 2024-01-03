#pragma once

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "ServerConfig.hpp"

class   Server {
public:
    Server(const ServerConfig& svconf);
    Server(const Server& server);

    Server& operator=(const Server& server);

    void            setServer(const ServerConfig& svconf);
    ServerConfig&   getServerConfig();
    const int&      getSocket() const;

private:
    ServerConfig    _svconf;
    int            _sockfd;
};

#endif
