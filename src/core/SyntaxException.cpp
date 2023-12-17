#include "SyntaxException.hpp"

bool    SyntaxException::hadError = false;

SyntaxException::~SyntaxException() throw() {
}

SyntaxException::SyntaxException(int line, const std::string& message, char c) {
    _errorMsg = std::string("[line ") + toString(line) + "] Error: " + message
                + c + ".";
}

SyntaxException::SyntaxException(int line, const std::string& where,
                                const std::string& message)
{
    _errorMsg = std::string("[line ") + toString(line) + "] Error: " + where
                + ": " + message;
}

const char* SyntaxException::what() const throw() {
    return _errorMsg.c_str();
}

std::string SyntaxException::toString(int nbr) {
    std::stringstream   ss;
    std::string         str;

    ss << std::dec << nbr;
    ss >> str;
    return str;
}
