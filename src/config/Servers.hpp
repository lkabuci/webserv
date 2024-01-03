#pragma once

#ifndef __SERVERS_HPP__
#define __SERVERS_HPP__

#include "Server.hpp"

class Servers {
  public:
    Servers();

    void                add(const Server& server);
    std::vector<Server> get();
    Server&             get(size_t i);

  private:
    std::vector<Server> _servers;
};

#endif
