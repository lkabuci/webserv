#pragma once

#include <iostream>
#include <poll.h>
#include <vector>

#include "IEventHandler.hpp"

class Dispatcher {
  public:
    static void
    dispatchEvents(const std::vector<pollfd>&         fds,
                   const std::vector<IEventHandler*>& eventHandlers);
};
