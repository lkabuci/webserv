#include "EventLoop.hpp"

EventLoop::EventLoop(int serverSocket)
    : _demultiplexer(serverSocket), _dispatcher(serverSocket) {}

void EventLoop::start() {
    // while (isServerRunning) {
    //     const int events = _demultiplexer.pollEvents();
    //     if (events == -1) {
    //         std::cerr << "Polling failed\n";
    //         break;
    //     }
    //     std::vector<pollfd>& fds = _demultiplexer.getDescriptors();
    //     _dispatcher.acceptConnection(fds);
    //     Dispatcher::processData(fds);
    // }
}
