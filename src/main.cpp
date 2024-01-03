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
    Servers servers = cp.getServers();

    return EXIT_SUCCESS;
}
