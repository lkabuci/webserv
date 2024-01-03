#include "../include/webserv.h"
#include "config/ServerConfig.hpp"
#include "reactor/Reactor.hpp"
#include "reactor/ServerEventHandler.hpp"
#include "reactor/Webserver.hpp"
#include "stream/Socket.hpp"

#include <csignal>
#include <vector>

bool isServerRunning = true;

void act(int signum) {
    std::cout << "Received SIGINT\n";
    isServerRunning = false;
}

int main(int argc, char* argv[]) {
    std::cout << "pid: " << getpid() << "\n";
    struct sigaction sa;
    std::memset(&sa, 0, sizeof sa);

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [config_file]" << std::endl;
        std::exit(USGERR);
    }
    ConfigParse cp;

    cp.parseFile(argv[1]);
    Socket server("0.0.0.0", "2222");

    Reactor& reactor = Reactor::getInstance();
    for (size_t i = 0; i < serverSockets.size(); ++i) {
        ServerEventHandler* serverHandler =
            new ServerEventHandler(serverSockets[i]);
        reactor.registerHandler(serverHandler, serverSockets[i]);
    }

    // Start the Reactor event loop
    reactor.run(serverSockets);

    return EXIT_SUCCESS;
}
