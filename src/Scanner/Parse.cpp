#include "Parse.hpp"

Parse::Parse() : _scanner("") {}

Parse::Parse(const std::string& source)
    : _scanner(source), _token(_scanner.get_next_token()), _prev(_token) {}

Parse::Parse(const Parse& parser)
    : _scanner(parser._scanner), _token(parser._token), _prev(parser._prev) {}

Parse& Parse::operator=(const Parse& parser) {
    if (this == &parser)
        return *this;
    _scanner = parser._scanner;
    _token = parser._token;
    _prev = parser._prev;
    return *this;
}

Token Parse::advance() {
    _prev = _token;
    _token = _scanner.get_next_token();
    return _prev;
}

Token Parse::previous() {
    return _prev;
}

Token Parse::peek() {
    return _token;
}

bool Parse::match(const TokenType& type) {
    if (_token.type() != type)
        return false;
    advance();
    return true;
}

bool Parse::check(const TokenType& type) {
    return _token.type() == type;
}

bool Parse::is_at_end() const {
    return _token.type() == END;
}

void Parse::consume(const TokenType& type, const char* message) {
    if (!match(type))
        throw std::runtime_error(message);
}

std::string Parse::get_line() {
    std::string line;

    while (!is_at_end() && !match(CR_LF))
        line.append(advance().lexeme());
    return line;
}
