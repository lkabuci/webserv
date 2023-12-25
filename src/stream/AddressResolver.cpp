#include "AddressResolver.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <vector>

AddressResolver::AddressResolver(const char* ip, const char* port)
    : _ip(ip), _port(port), _addresses(NULL) {
    fillAddressInfo();
}

const struct addrinfo* AddressResolver::getAddresses() const {
    return _addresses;
}

void AddressResolver::fillAddressInfo() {
    struct addrinfo hints;

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // IPV4 and IPV6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

    const int rv = getaddrinfo(_ip, _port, &hints, &_addresses);
    if (rv != 0) {
        std::cerr << "getaddeinfo: " << gai_strerror(rv) << ".\n";
        std::exit(EXIT_FAILURE);
    }
}

AddressResolver::~AddressResolver() {
    freeaddrinfo(_addresses);
}
