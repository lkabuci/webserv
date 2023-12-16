#include "ParseException.hpp"
#include "ConfigParse.hpp"

ParseException::ParseException(Token token, const std::string& message) {
    if (token.getType() == END) {
        _errorMsg = "[" + ConfigParse::toString(token.getLine()) + "] at end: "
                    + message;
    } else {
        _errorMsg = "[" + ConfigParse::toString(token.getLine()) + "] at '"
                    + token.getLexeme() + "': " + message;
    }
}

const char* ParseException::what() const throw() {
    return _errorMsg.c_str();
}
