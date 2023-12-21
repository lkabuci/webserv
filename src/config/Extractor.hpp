#pragma once

#ifndef __EXTRACTOR_HPP__
#define __EXTRACTOR_HPP__

#include "Expr.hpp"

class   Extractor {
public:
    static size_t                           port_number(Parameter& expr);
    static std::vector<std::string>         server_name(Parameter& expr);
    static size_t                       max_client_body_size(Parameter& expr);
    static std::map<uint16_t, std::string>  error_page(Parameter& expr);
    static std::vector<std::string>         index_files(Parameter& expr);
    static std::string                      root_dir(Parameter& expr);
    static bool                             autoindex(Parameter& expr);

private:
    Extractor();
};

#endif
