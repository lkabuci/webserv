#include "Token.hpp"

std::map<TokenType, std::string>  Token::values = createValuesMap();

std::map<TokenType, std::string>  Token::createValuesMap() {
    std::map<TokenType, std::string>  values;

    values[PARAMETER] = "PARAMETER";
    values[LEFT_BRACE] = "LEFT_BRACE";
    values[RIGHT_BRACE] = "RIGHT_BRACE";
    values[SEMICOLON] = "SEMICOLON";
    values[SERVER_CONTEXT] = "SERVER_CONTEXT";
    values[LISTEN] = "LISTEN";
    values[ROOT] = "ROOT";
    values[CLIENT_MAX_BODY_SIZE] = "CL_MBS";
    values[ERROR_PAGE] = "ERROR_PAGE";
    values[INDEX] = "INDEX";
    values[LOCATION_CONTEXT] = "LOCATION_CONTEXT";
    values[AUTOINDEX] = "AUTOINDEX";
    values[ALLOW_METHODS] = "ALLOW_METHODS";
    values[RETURN] = "RETURN";
    values[SERVER_NAME] = "SERV_NAME";
    return values;
}

Token::Token() : _type(END), _lexeme(), _line(0) {}

Token::Token(TokenType type, const std::string& lexeme, size_t line)
    : _type(type)
    , _lexeme(lexeme)
    , _line(line)
{
}

Token::Token(const Token& t)
    : _type(t._type)
    , _lexeme(t._lexeme)
    , _line(t._line)
{
}
Token&  Token::operator=(const Token& t) {
    _type = t._type;
    _lexeme = t._lexeme;
    _line = t._line;
    return *this;
}

bool    Token::operator==(const Token& t) {
    return _lexeme == t._lexeme && _type == t._type && _line == t._line;
}

TokenType   Token::getType() const { return _type; }

const std::string&    Token::getLexeme() const { return _lexeme; }

const size_t&   Token::getLine() const { return _line; }

std::ostream&   operator<<(std::ostream& os, const Token& token) {
    os << "[" << token.values[token.getType()] << "]:\t" << token.getLexeme()
        << ",\tline: " << token.getLine();
    return os;
}
