#include "Dispatcher.hpp"

void Dispatcher::dispatchEvents(
    const std::vector<pollfd>&         fds,
    const std::vector<IEventHandler*>& eventHandlers) {
    for (size_t i = 0; i < fds.size(); ++i) {
        // loop till servers then till clients
        if (fds[i].revents & POLLIN) {
            // Dispatch event to the corresponding handler
            eventHandlers[i]->handleEvent();
        }
        // Add conditions for other events (POLLERR, POLLOUT, etc.), handle them
    }
}
