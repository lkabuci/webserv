#include "Demultiplexer.hpp"
#include "Reactor.hpp"
#include <iostream>

int Demultiplexer::waitForEvents() {
    return poll(Reactor::getInstance().getPollfds().data(),
                Reactor::getInstance().getPollfds().size(), -1);
}
