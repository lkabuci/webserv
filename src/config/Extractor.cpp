#include "Extractor.hpp"

size_t  Extractor::port_number(Parameter &expr) {
    std::vector<std::string>    parameters = expr.getParams();

    if (parameters.size() != 1)
        throw std::runtime_error("Invalid port number");
    std::stringstream   ss(parameters[0]);
    int                 port = 0;

    if (!(ss >> port) || port < 0 || port < 1024 || port > 49151)
        throw std::runtime_error("Invalid port number");
    if (port < 1024 || port > 49151)
        throw std::runtime_error("Invalid range of the port number:"
                                " 1024 <= port <= 49151");
    return port;
}
