#include "Extractor.hpp"
#include "RunTimeException.hpp"
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

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

std::set<std::string>    Extractor::server_name() {
    if (_info.empty())
        throw RunTimeException(_token, "Invalid server name.");
    std::set<std::string>   server_name;

    server_name.insert(_info.begin(), _info.end());
    return server_name;
}

size_t  Extractor::client_max_body_size() {
    if (_info.size() != 2)
        throw RunTimeException(_token, "Invalid value.");
    std::stringstream   ss(_info[0]);
    int                 size;

    if (!(ss >> size) || size < 0)
        throw RunTimeException(_token, "Invalid value.");
    if (_info[1].size() != 1 || _info[1][0] != 'm')
        throw RunTimeException(_token, "Invalid size.");
    return size;
}

std::set<std::string>    Extractor::index() {
    if (_info.empty())
        throw RunTimeException(_token, "Invalid index.");
    std::set<std::string>   index;

    index.insert(_info.begin(), _info.end());
    return index;
}

std::set<std::string>    Extractor::root() {
    if (_info.empty())
        throw RunTimeException(_token, "Invalid root.");
    std::set<std::string>   root;

    root.insert(_info.begin(), _info.end());
    return root;
}

std::map<size_t, std::string>   Extractor::error_page() {
    if (_info.size() < 2)
        throw RunTimeException(_token, "Invalid error_page.");

    std::map<size_t, std::string>   error_page;
    std::string                     path = _info[_info.size() - 1];
    std::stringstream               ss;
    int                             code;

    for (size_t i = 0; i < _info.size() - 1; ++i) {
        ss << _info[i];
        if (!(ss >> code) || code < 100 || code > 599)
            throw RunTimeException(_token, "Invalid error_page code.");
        error_page[code] = path;
        ss.clear();
    }
    return error_page;
}

std::map<size_t, std::string>   Extractor::return_page() {
    if (_info.size() < 2)
        throw RunTimeException(_token, "Invalid return_page.");
    std::stringstream               ss;
    std::map<size_t, std::string>   return_page;
    std::string                     path = _info[_info.size() - 1];
    int                             code;

    for (size_t i = 0; i < _info.size() - 1; i++) {
        ss << _info[i];
        if (!(ss >> code) || code < 100 || code > 599)
            throw RunTimeException(_token, "Invalid return_page code.");
        return_page[code] = path;
        ss.clear();
    }
    return return_page;
}

bool    Extractor::autoindex() {
    if (_info.size() != 1)
        throw RunTimeException(_token, "Invalid autoindex.");
    if (_info[0] == "on")
        return true;
    else if (_info[0] == "off")
        return false;
    throw RunTimeException(_token, "Invalid autoindex value.");
}
