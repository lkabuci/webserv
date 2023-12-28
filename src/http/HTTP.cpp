#include "HTTP.hpp"
#include <map>
#include <stdexcept>
#include <string>

std::string HTTP::toString(HTTP::VERSION version) {
    switch (version) {
    case HTTP::HTTP_1_0:
        return "HTTP/1.0";
    case HTTP::HTTP_1_1:
        return "HTTP/1.1";
    case HTTP::HTTP_2_0:
        return "HTTP/2.0";
    }
    throw std::runtime_error("Unsupported version");
}

HTTP::VERSION HTTP::toVersion(const std::string& version) {
    std::map<std::string, HTTP::VERSION> versionMap;
    versionMap["HTTP/1.0"] = HTTP::HTTP_1_0;
    versionMap["HTTP/1.1"] = HTTP::HTTP_1_1;
    versionMap["HTTP/2.0"] = HTTP::HTTP_2_0;

    std::map<std::string, HTTP::VERSION>::iterator it =
        versionMap.find(version);
    if (it != versionMap.end())
        return it->second;
    throw std::runtime_error("not supported http version");
}

std::string HTTP::toString(HTTP::METHOD method) {
    switch (method) {
    case HTTP::GET:
        return "GET";
    case HTTP::POST:
        return "POST";
    case HTTP::PUT:
        return "PUT";
    case HTTP::DELETE:
        return "DELETE";
    }
    throw std::runtime_error("Unsupported method");
}

HTTP::METHOD HTTP::toMethod(const std::string& method) {
    std::map<std::string, HTTP::METHOD> methodMap;
    methodMap["GET"] = HTTP::GET;
    methodMap["POST"] = HTTP::POST;
    methodMap["PUT"] = HTTP::PUT;
    methodMap["DELETE"] = HTTP::DELETE;

    std::map<std::string, HTTP::METHOD>::iterator it = methodMap.find(method);
    if (it != methodMap.end())
        return it->second;
    throw std::runtime_error("not supported http method");
}
