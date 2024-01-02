#include "Extractor.hpp"
#include "RunTimeException.hpp"
#include <algorithm>

std::vector<std::string> Extractor::_allow_methods;

Extractor::Extractor(const std::vector<std::string>& info, const Token& token)
    : _info(info), _token(token) {
    _allow_methods.push_back("GET");
    _allow_methods.push_back("POST");
    _allow_methods.push_back("DELETE");
    _allow_methods.push_back("PUT");
}

std::vector<std::string> Extractor::ip_port() {
    if (_info.size() != 1)
        throw RunTimeException(_token, "Invalid port number.");

    size_t pos = _info[0].find(':');
    if (pos == std::string::npos)
        throw RunTimeException(_token, "Invalid port number.");

    std::string ip;
    std::string port;

    ip = _info[0].substr(0, pos);
    port = _info[0].substr(pos + 1, _info[0].length());
    if (ip.empty())
        ip = "localhost";
    if (port.empty())
        port = "8000";
    std::vector<std::string> ipport;

    ipport.push_back(ip);
    ipport.push_back(port);
    return ipport;
    // int port;

    // if (!(ss >> port) || port < 0)
    //     throw RunTimeException(_token, "Invalid port number.");
    // return port;
}

std::set<std::string> Extractor::server_name() {
    if (_info.empty())
        throw RunTimeException(_token, "Invalid server name.");
    std::set<std::string> server_name;

    server_name.insert(_info.begin(), _info.end());
    return server_name;
}

size_t Extractor::client_max_body_size() {
    if (_info.size() != 1)
        throw RunTimeException(_token, "Invalid value.");
    std::string info = _info[0];
    if (info[info.length() - 1] != 'm')
        throw RunTimeException(_token, "Invalid size.");
    info.pop_back();
    std::stringstream ss(info);
    int               size;

    if (!(ss >> size) || size < 0)
        throw RunTimeException(_token, "Invalid value.");
    return size;
}

std::set<std::string> Extractor::index() {
    if (_info.empty())
        throw RunTimeException(_token, "Invalid index.");
    std::set<std::string> index;

    index.insert(_info.begin(), _info.end());
    return index;
}

std::set<std::string> Extractor::root() {
    if (_info.empty())
        throw RunTimeException(_token, "Invalid root.");
    std::set<std::string> root;

    root.insert(_info.begin(), _info.end());
    return root;
}

std::map<size_t, std::string> Extractor::error_page() {
    if (_info.size() < 2)
        throw RunTimeException(_token, "Invalid error_page.");

    std::map<size_t, std::string> error_page;
    std::string                   path = _info[_info.size() - 1];
    std::stringstream             ss;
    int                           code;

    for (size_t i = 0; i < _info.size() - 1; ++i) {
        ss << _info[i];
        if (!(ss >> code) || code < 100 || code > 599)
            throw RunTimeException(_token, "Invalid error_page code.");
        error_page[code] = path;
        ss.clear();
    }
    return error_page;
}

std::map<size_t, std::string> Extractor::return_page() {
    if (_info.size() < 2)
        throw RunTimeException(_token, "Invalid return_page.");
    std::stringstream             ss;
    std::map<size_t, std::string> return_page;
    std::string                   path = _info[_info.size() - 1];
    int                           code;

    for (size_t i = 0; i < _info.size() - 1; i++) {
        ss << _info[i];
        if (!(ss >> code) || code < 100 || code > 599)
            throw RunTimeException(_token, "Invalid return_page code.");
        return_page[code] = path;
        ss.clear();
    }
    return return_page;
}

std::set<std::string> Extractor::allow_methods() {
    if (_info.empty())
        throw RunTimeException(_token, "allow_methods can't be empty.");
    if (_info.size() > 4)
        throw RunTimeException(_token, "only GET, POST, DELETE and PUT"
                                       " are allowed.");
    std::set<std::string> allow_methods;

    for (size_t i = 0; i < _info.size(); ++i) {
        if (std::find(_allow_methods.begin(), _allow_methods.end(), _info[i]) ==
            _allow_methods.end())
            throw RunTimeException(_token, _info[i] + " is not a valid "
                                                      "method.");
    }
    allow_methods.insert(_info.begin(), _info.end());
    return allow_methods;
}

bool Extractor::autoindex() {
    if (_info.size() != 1)
        throw RunTimeException(_token, "Invalid autoindex.");
    if (_info[0] == "on")
        return true;
    else if (_info[0] == "off")
        return false;
    throw RunTimeException(_token, "Invalid autoindex value.");
}
