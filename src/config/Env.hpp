#pragma once

#ifndef __ENV_HPP__
#define __ENV_HPP__

#include "ServerConfig.hpp"
#include "Token.hpp"
#include "Extractor.hpp"

class   Env {
public:
    ~Env();

    static void create(TokenType type);
    static void put(const std::vector<std::string>& value, const Token& token);
    static void add(TokenType type);
    static void remove();

    static std::vector<ServerConfig>    get();

private:
    Env();

    static ConfigInfo*                  _ptr;
    static ConfigInfo*                  _prev;
    static std::vector<ServerConfig>    _svconfs;
};

#endif
