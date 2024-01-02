#pragma once

#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <vector>

class Client;

class Dispatcher {
  public:
    explicit Dispatcher(int serverSocket);

    void        acceptConnection(std::vector<pollfd>&) const;
    static void processData(std::vector<pollfd>& fds);

  private:
    int _serverSocket;

    static void addClientSocketToPollList(std::vector<pollfd>&,
                                          std::vector<Client>&,
                                          struct sockaddr_storage&, int);
    static void closeConnectionOnClient(std::vector<pollfd>&,
                                        std::vector<pollfd>::iterator&);
};
