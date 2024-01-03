#include "../include/webserv.h"
#include "reactor/Reactor.hpp"
#include "reactor/ServerEventHandler.hpp"

#include "utils/SignalHandler.hpp"
#include <csignal>
#include <vector>

volatile sig_atomic_t isServerRunning = true;

int main(int argc, char* argv[]) {
    std::cout << "pid: " << getpid() << "\n";
    SignalHandler signalHandler;
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [config_file]" << std::endl;
        std::exit(USGERR);
    }
    ConfigParse cp;

    cp.parseFile(argv[1]);
    Servers& servers = cp.getServers();

    Reactor& reactor = Reactor::getInstance();
    for (size_t i = 0; i < servers.size(); ++i) {
        ServerEventHandler* serverHandler =
            new ServerEventHandler(servers[i]->getSocket());
        reactor.registerHandler(serverHandler, servers[i]->getSocket());
    }

    // Start the Reactor event loop
    // note that this only approach for testing and run the reactor this
    // structure will be changed later on
    std::vector<int> serverSockets;
    for (size_t i = 0; i < servers.size(); ++i) {
        serverSockets.push_back(servers[i]->getSocket());
    }
    reactor.run(serverSockets);

    return EXIT_SUCCESS;
}
