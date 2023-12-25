#include "RunTimeException.hpp"
#include "ConfigParse.hpp"

RunTimeException::RunTimeException(const Token& token,
                                   const std::string& message) {
    if (token.type() == END) {
        _errMsg = "[line " + ConfigParse::toString(token.line()) +
                  "] at end: " + message;
        return;
    } else {
        _errMsg = "[line " + ConfigParse::toString(token.line()) + "] at '" +
                  token.lexeme() + "': " + message;
    }
}

RunTimeException::~RunTimeException() throw() {}

const char* RunTimeException::what() const throw() { return _errMsg.c_str(); }
