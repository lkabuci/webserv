#pragma once

#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include "common.hpp"

class   Token {
public:
    Token();
    Token(TokenType type, const std::string& lexeme, size_t line);
    Token(const Token& t);

    Token&  operator=(const Token& t);

    static std::map<TokenType, std::string>   m;
    static std::map<TokenType, std::string>   createMap();

    TokenType           getType() const;
    const std::string&  getLexeme() const;
    const size_t&       getLine() const;

private:
    TokenType   _type;
    std::string _lexeme;
    size_t      _line;
};

std::ostream&   operator<<(std::ostream& os, const Token& token);

#endif
