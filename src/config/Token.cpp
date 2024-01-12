#include "Token.hpp"
#include "TokenType.hpp"

Token::Token() : _type(END), _lexeme(""), _line(0) {}

Token::Token(const TokenType& type, const std::string& lexeme, const int& line)
    : _type(type), _lexeme(lexeme), _line(line) {}

Token::Token(const TokenType& type, const std::string& lexeme)
    : _type(type), _lexeme(lexeme) {}

Token::Token(const Token& token)
    : _type(token._type), _lexeme(token._lexeme), _line(token._line) {}

Token::~Token() {}

Token& Token::operator=(const Token& token) {
    if (this == &token)
        return *this;
    _type = token._type;
    _lexeme = token._lexeme;
    _line = token._line;
    return *this;
}

const TokenType& Token::type() const {
    return _type;
}

const std::string& Token::lexeme() const {
    return _lexeme;
}

const int& Token::line() const {
    return _line;
}
