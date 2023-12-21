#pragma once

#include <netdb.h>
#include <vector>

class AddressResolver {
  public:
    explicit AddressResolver(const char* ip, const char* port);
    std::vector<struct addrinfo> getAddresses() const;

  private:
    std::vector<struct addrinfo> _addresses;
    const char* _port;
    const char* _ip;

    void fillAddressInfo(std::vector<struct addrinfo>&);

    AddressResolver(const AddressResolver&);
    AddressResolver& operator=(AddressResolver&);
};
