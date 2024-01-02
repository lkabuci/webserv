#include "Dispatcher.hpp"
#include "../../include/webserv.h"
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

Dispatcher::Dispatcher(int serverSocket) : _serverSocket(serverSocket) {}

// Loop through all servers
void Dispatcher::acceptConnection(std::vector<pollfd>& fds) const {
    /*
     * TODO: a for loop to check all servers
     * for (int i = 0; i < servers.size(); ++i) {
     *     if pfds[i].revents & POLLIN:
     *          same as before
     * }
     */
    if (fds[0].revents & POLLIN) {
        struct sockaddr_storage clientAddr;
        int                     clientSocket;
        socklen_t               clientAddrLen = sizeof clientAddr;
        clientSocket = accept(_serverSocket,
                              reinterpret_cast<struct sockaddr*>(&clientAddr),
                              &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << "Error accepting connection\n";
            return;
        }
        std::vector<Client> clients = std::vector<Client>();
        addClientSocketToPollList(fds, clients, clientAddr, clientSocket);
    }
}

// Loop through a list of clients
void Dispatcher::processData(std::vector<pollfd>& fds) {
    std::vector<struct pollfd>::iterator it;
    for (it = fds.begin() + 1; it != fds.end(); ++it) {
        if (it->revents & POLLHUP) {
            closeConnectionOnClient(fds, it);
            continue;
        }
        if (it->revents & POLLIN) {
            char msg[BUFFER_SIZE];
            std::memset(msg, 0, sizeof msg);

            ssize_t nbytes = recv(it->fd, msg, BUFFER_SIZE - 1, 0);
            // TODO: append the received data to a std::string

            switch (nbytes) {
            case -1:
                std::cout << "Error: " << std::strerror(errno) << std::endl;
                closeConnectionOnClient(fds, it);
                break;
            case 0:
                std::cout << "- Connection Closed\n";
                closeConnectionOnClient(fds, it);
                break;
            default:
                //                done reading the data
                std::cout << "No more to read\n";
                if (nbytes < BUFFER_SIZE - 1) {
                    //                    isDoneReading = true;
                    break;
                } else
                    continue;
            }
            break;
        }
    }
}

void Dispatcher::addClientSocketToPollList(std::vector<pollfd>& fds,
                                           std::vector<Client>& clients,
                                           sockaddr_storage& addr, int socket) {

    Client client(addr, socket);
    fds.push_back(client.getPfd());
    //    clients.push_back(client);
    std::cout << "+ New Client Joined: " << client.getClientAddress() << "\n";

    // now how can I keep track of the client classes;

    // struct pollfd clientPollFd;
    // std::memset(&clientPollFd, 0, sizeof(clientPollFd));
    // clientPollFd.fd = socket;
    // clientPollFd.events = POLLIN;
    // clientPollFd.revents = 0;
    // fds.push_back(clientPollFd);
}

void Dispatcher::closeConnectionOnClient(
    std::vector<pollfd>& pfds, std::vector<pollfd>::iterator& position) {
    close(position->fd);
    pfds.erase(position);
}
