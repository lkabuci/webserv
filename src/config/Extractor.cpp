#include "Extractor.hpp"

Extractor::Extractor(const std::vector<std::string>& info, const Token& token)
    : _info(info)
    , _token(token)
{
}

size_t  Extractor::port_number() {
    if (_info.size() != 1)
        throw RunTimeException(_token, "Invalid port number.");
    std::stringstream   ss(_info[0]);
    int                 port;

    if (!(ss >> port))
        throw RunTimeException(_token, "Invalid port number.");
    if (port < 1024 || port > 49151)
        throw RunTimeException(_token, "port number should be in the registered"
                                " ports: 1024 to 49151.");
    return port;
}
