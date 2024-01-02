#include "Reactor.hpp"
#include "../../include/webserv.h"

Reactor& Reactor::getInstance() {
    static Reactor instance;
    return instance;
}

void Reactor::registerHandler(IEventHandler* handler) {
    _eventHandlers.push_back(handler);
}

void Reactor::run(const std::vector<int>& sockets) {
    while (isServerRunning) {
        std::vector<pollfd> fds = _demultiplexer.waitForEvents(sockets);
        _dispatcher.dispatchEvents(fds, _eventHandlers);
    }
}

void Reactor::unregisterHandler(IEventHandler* handler) {
    std::vector<IEventHandler*>::iterator it =
        std::find(_eventHandlers.begin(), _eventHandlers.end(), handler);
    if (it == _eventHandlers.end())
        return;
    _eventHandlers.erase(it);
}
