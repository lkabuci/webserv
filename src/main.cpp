#include "reactor/EventLoop.hpp"
#include "stream/Socket.hpp"
#include <cstdlib>

int main() {
    Socket server("0.0.0.0", "2222");

    int serverSocket = server.getSocketfd();

    EventLoop eventLoop(serverSocket);
    eventLoop.start();

    return EXIT_SUCCESS;
}
