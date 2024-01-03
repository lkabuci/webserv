#include "../include/webserv.h"
#include "config/ServerConfig.hpp"
#include "reactor/Reactor.hpp"
#include "reactor/ServerEventHandler.hpp"
#include "reactor/Webserver.hpp"
#include "stream/Socket.hpp"

#include <csignal>
#include <vector>
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
/*
   TODO: add logger as well, it will behave like nginx
   we can have the builder design pattern for logger
   base class Logger
   derived classes: ConnectionLoger, ErrorLoger, AccessLoger
   at the end it should be like this when calling it
   * Error Logs (error level):
       2024/01/02 12:34:56 [error] 1234#1234: *56789 open() "/path/to/file"
   failed (2: No such file or directory)
        [date] [time] [level] [ip] [port]
   [message]
   * Access Logs (info level):
       192.168.1.100 - - [02/Jan/2024:12:34:56 +0000] "GET /example HTTP/1.1"
   200 1234 "-" "Mozilla/5.0 ..."
        [ip] [date] [time] [request] [status] [size] [user_agent]
   * Info Logs (info level):
       2024/01/02 12:34:56 [info] 1234#1234: *56789 client closed connection
   (time=0.123) 2024/01/02 12:34:56 [info] 1234#1234: *56789 client
        [date] [time] [level] [ip] [port] [message]
*/
bool isServerRunning = true;

void act(int signum) {
    std::cout << "Received SIGINT\n";
    isServerRunning = false;
}

int main(int argc, char* argv[]) {
    std::cout << "pid: " << getpid() << "\n";
    struct sigaction sa;
    std::memset(&sa, 0, sizeof sa);

    sa.sa_handler = act;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    Socket server("0.0.0.0", "2222");
    Socket server2("0.0.0.0", "3333");
    Socket server3("0.0.0.0", "4444");

    std::vector<int> serverSockets(3);
    serverSockets[0] = server.getSocketfd();
    serverSockets[1] = server2.getSocketfd();
    serverSockets[2] = server3.getSocketfd();

    Reactor& reactor = Reactor::getInstance();
    for (size_t i = 0; i < serverSockets.size(); ++i) {
        ServerEventHandler* serverHandler =
            new ServerEventHandler(serverSockets[i]);
        reactor.registerHandler(serverHandler, serverSockets[i]);
    }

    // Start the Reactor event loop
    reactor.run(serverSockets);

    //    Webserver webserver(serverSockets);
    //    webserver.start();

    return 0;
}
