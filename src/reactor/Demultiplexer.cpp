#include "Demultiplexer.hpp"
#include <iostream>

std::vector<pollfd>
Demultiplexer::waitForEvents(const std::vector<int>& sockets) {
    std::vector<pollfd> fds;
    for (size_t i = 0; i < sockets.size(); ++i) {
        pollfd pfd = {sockets[i], POLLIN, 0};
        fds.push_back(pfd);
    }
    int ret = poll(fds.data(), fds.size(), -1);
    if (ret == -1) {
        std::cerr << "Polling failed" << std::endl;
        // Handle error
    }
    return fds;
}
