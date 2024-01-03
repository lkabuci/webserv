#pragma once

#ifndef __SERVERS_HPP__
#define __SERVERS_HPP__

#include "Server.hpp"

class Servers {
  public:
    Servers();
    ~Servers();

    void                 add(Server* server);
    std::vector<Server*> get();
    size_t               size() const;
    Server*              operator[](size_t i);

  private:
    std::vector<Server*> _servers;
};

#endif
