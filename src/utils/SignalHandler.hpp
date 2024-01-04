#pragma once
#include "../../include/webserv.hpp"
#include <csignal>
#include <cstring>

class SignalHandler {
  public:
    SignalHandler();

  private:
    static void handleSIGINT(int signum);
};
