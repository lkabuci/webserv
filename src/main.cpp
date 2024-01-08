#include "../include/webserv.hpp"
#include "Webserver.hpp"

#include "utils/SignalHandler.hpp"
#include <csignal>
#include <unistd.h>

volatile sig_atomic_t isServerRunning = true;

int main(int argc, char* argv[]) {
    std::cout << "pid: " << getpid() << "\n";
    SignalHandler signalHandler;
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [config_file]" << std::endl;
        std::exit(USGERR);
    }
    ConfigParse cp(argv[1]);
    Servers&    servers = cp.getServers();
    Webserver   webserver(servers);
    Webserver::run();

    return EXIT_SUCCESS;
}
