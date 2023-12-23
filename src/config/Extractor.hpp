#pragma once

#ifndef __EXTRACTOR_HPP__
#define __EXTRACTOR_HPP__

#include "RunTimeException.hpp"

class   Extractor {
public:
    Extractor(const std::vector<std::string>& info, const Token& token);

    size_t                          port_number();
    std::set<std::string>           server_name();
    size_t                          client_max_body_size();
    std::set<std::string>           index();
    std::set<std::string>           root();
    std::map<size_t, std::string>   error_page();
    std::map<size_t, std::string>   return_page();
    bool                            autoindex();

private:
    Extractor(const Extractor&);
    Extractor&  operator=(const Extractor&);

    std::vector<std::string>    _info;
    Token                       _token;
};

#endif
