#include "Dispatcher.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

Dispatcher::Dispatcher(int serverSocket) : _serverSocket(serverSocket) {}

void Dispatcher::acceptConnection(std::vector<pollfd>& fds) {
    if (fds[0].revents & POLLIN) {
        struct sockaddr_in clientAddr;
        socklen_t          clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(_serverSocket, (struct sockaddr*)&clientAddr,
                                  &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << "Error accepting connection\n";
            return;
        }

        std::cout << "Accepted connection from "
                  << inet_ntoa(clientAddr.sin_addr) << ":"
                  << ntohs(clientAddr.sin_port) << "\n";
        // Add client socket to poll list
        struct pollfd clientPollFd;
        std::memset(&clientPollFd, 0, sizeof(clientPollFd));
        clientPollFd.fd = clientSocket;
        clientPollFd.events = POLLIN;
        clientPollFd.revents = 0;
        fds.push_back(clientPollFd);
    }
}

void Dispatcher::processData(std::vector<pollfd>& fds) {
    std::vector<struct pollfd>::iterator it;
    for (it = fds.begin() + 1; it != fds.end(); ++it) {
        if (it->revents & POLLIN) {
            // Handle data from client
            // process the data here
            close(it->fd);
            fds.erase(it);
            break;
        }
    }
}
