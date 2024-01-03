#pragma once
#include "../../include/webserv.h"
#include <csignal>
#include <cstring>

class SignalHandler {
  public:
    SignalHandler();

  private:
    static void handleSIGINT(int signum);
};
