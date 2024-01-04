#pragma once

#include "stream/Servers.hpp"

class Webserver {
  public:
    explicit Webserver(Servers&);
    static void run();

  private:
    Servers& _servers;
    void     _setup();
};
