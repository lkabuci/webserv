#include "../include/webserv.h"

/*
 * the server fds they will be first pushed to the list vector<struct pollfds>
 * <pollfds> (server1, server2, server3, ..., servern)
 * then we will create a client class for each new connection it should be a
 * list of vectors as well <Clients>(client1, client2, ..., clientn)
 * but the problem is how can I make it synchronous like remove a client it
 * should remove it's fd from the list of pollfds, or maybe just setting it
 * to -1, and every period of time run through all of them and remove the
 * ones that have negative values
 */

int main(int argc, char* argv[]) {
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
