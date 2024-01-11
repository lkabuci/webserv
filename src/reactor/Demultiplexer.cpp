#include "Demultiplexer.hpp"
#include "Reactor.hpp"
#include <iostream>

int Demultiplexer::waitForEvents() {
    std::vector<pollfd>& pfds = Reactor::getInstance().getPollfds();
    return poll(pfds.data(), pfds.size(), -1);
}
