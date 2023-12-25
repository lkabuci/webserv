#pragma once

#ifndef __CONFIG_PARSE_HPP__
#define __CONFIG_PARSE_HPP__

#include "Lexer.hpp"
#include "SyntaxException.hpp"
#include "Token.hpp"
#include "common.hpp"

class ConfigParse {
  public:
    ConfigParse();
    void parseFile(const char* file);

    static std::string toString(int n);

    // private:
    ConfigParse(const ConfigParse&);
    ConfigParse& operator=(const ConfigParse&);

    void _parse(const std::string& source);
};

#endif
