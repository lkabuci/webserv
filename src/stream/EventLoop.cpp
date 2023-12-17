#include "EventLoop.hpp"
#include <cstring>

std::vector<struct pollfd> EventLoop::_pollfds;

// Note: try catch if can't add the client
void EventLoop::addClient(int clientFD) {
    struct pollfd clientStruct;
    std::memset(&clientStruct, 0, sizeof(clientStruct));
    clientStruct.fd = clientFD;
    clientStruct.events = POLLIN;
    _pollfds.push_back(clientStruct);
}

void EventLoop::removeClient(int clientIndex) {
    close(_pollfds[clientIndex].fd);
    _pollfds.erase(_pollfds.begin() + clientIndex);
}

bool EventLoop::isEventSet(int index, short event) {
    return _pollfds[index].revents & event;
}

void EventLoop::setEvent(int index, short event) {
    _pollfds[index].events = event;
}

size_t EventLoop::getSize(void) { return _pollfds.size(); }

int EventLoop::getFd(int index) { return _pollfds[index].fd; }
