#pragma once

#include <netdb.h>
#include <vector>

class AddressResolver {
  public:
    explicit AddressResolver(const char* ip, const char* port);
    ~AddressResolver();
    const struct addrinfo* getAddresses() const;

  private:
    struct addrinfo* _addresses;
    const char*      _port;
    const char*      _ip;

    void fillAddressInfo();

    AddressResolver(const AddressResolver&);
    AddressResolver& operator=(AddressResolver&);
};
