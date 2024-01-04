#include "Reactor.hpp"
#include "../../include/webserv.hpp"
#include <unistd.h>

Reactor& Reactor::getInstance() {
    static Reactor instance;
    return instance;
}

void Reactor::registerHandler(IEventHandler* handler, int socket) {
    _eventHandlers.push_back(handler);
    pollfd newPfd = {socket, POLLIN, 0};
    _pollfds.push_back(newPfd);
}

void Reactor::run() {
    while (isServerRunning) {
        if (_demultiplexer.waitForEvents() == -1) {
            break;
        }
        _dispatcher.dispatchEvents(_pollfds, _eventHandlers);
    }
}

void Reactor::unregisterHandler(IEventHandler* handler) {
    std::vector<IEventHandler*>::iterator it =
        std::find(_eventHandlers.begin(), _eventHandlers.end(), handler);
    if (it != _eventHandlers.end()) {
        long index = std::distance(_eventHandlers.begin(), it);
        delete *it;
        _eventHandlers.erase(_eventHandlers.begin() + index);
        _pollfds.erase(_pollfds.begin() + index);
    }
}

std::vector<pollfd>& Reactor::getPollfds() {
    return _pollfds;
}

Reactor::~Reactor() {
    for (std::vector<IEventHandler*>::iterator it = _eventHandlers.begin();
         it != _eventHandlers.end(); ++it) {
        delete *it;
    }
    for (std::vector<pollfd>::iterator it = _pollfds.begin();
         it != _pollfds.end(); ++it) {
        close(it->fd);
    }
    _eventHandlers.clear();
    _pollfds.clear();
}
