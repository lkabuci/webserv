#include "../include/webserv.h"

int main() {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [config_file]" << std::endl;
        std::exit(USGERR);
    }
    ConfigParse cp;

    cp.parseFile(argv[1]);
    Socket server("0.0.0.0", "2222");

    int serverSocket = server.getSocketfd();

    EventLoop eventLoop(serverSocket);
    eventLoop.start();

    return EXIT_SUCCESS;
}
