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
    bool    operator==(const Token& t);

    static std::map<TokenType, std::string>   values;
    static std::map<std::string, TokenType>   types;
    static std::map<TokenType, std::string>   createValuesMap();
    static TokenType    getLexemeType(const std::string& type);

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
