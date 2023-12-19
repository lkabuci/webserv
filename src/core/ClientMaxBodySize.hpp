#pragma once

#ifndef __CLIENT_MAX_BODY_SIZE_HPP__
#define __CLIENT_MAX_BODY_SIZE_HPP__

#include "common.hpp"

class   ClientMaxBodySize {
public:
    enum    SIZE_UNIT {
        BYTE, KILO, MEGA, GEGA
    };

    ClientMaxBodySize(const std::vector<std::string>& sizeStr);
    ClientMaxBodySize(const ClientMaxBodySize& cmbs);
    ~ClientMaxBodySize();

    ClientMaxBodySize&  operator=(const ClientMaxBodySize& cmbs);

private:
    static std::map<std::string, SIZE_UNIT> _units;

    std::vector<std::string>    _sizeStr;
    size_t                      _size;
};

#endif
