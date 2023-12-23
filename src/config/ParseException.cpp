#include "ParseException.hpp"
#include "ConfigParse.hpp"

ParseException::ParseException(Token token, const std::string& message) {
    if (token.type() == END) {
        _errorMsg = "[line " + ConfigParse::toString(token.line())
                    + "] at end: " + message;
    } else {
        _errorMsg = "[line " + ConfigParse::toString(token.line()) + "] at '"
                    + token.lexeme() + "': " + message;
    }
}

const char* ParseException::what() const throw() {
    return _errorMsg.c_str();
}
