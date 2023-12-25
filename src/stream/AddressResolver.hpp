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
    const char*      _ip;
    const char*      _port;

    void fillAddressInfo();

    AddressResolver(const AddressResolver&);
    AddressResolver& operator=(AddressResolver&);
};
