#include "Token.hpp"

std::map<TokenType, std::string>  Token::m = createMap();

std::map<TokenType, std::string>  Token::createMap() {
    std::map<TokenType, std::string>  m;

    m[PARAMETER] = "PARAMETER";
    m[NUMBER] = "NUMBER";
    m[LEFT_BRACE] = "LEFT_BRACE";
    m[RIGHT_BRACE] = "RIGHT_BRACE";
    m[SEMICOLON] = "SEMICOLON";
    m[SERVER_BLOCK] = "SERVER_BLOCK";
    m[LISTEN] = "LISTEN";
    m[ROOT] = "ROOT";
    m[CLIENT_MAX_BODY_SIZE] = "CL_MBS";
    m[ERROR_PAGE] = "ERROR_PAGE";
    m[INDEX] = "INDEX";
    m[LOCATION] = "LOCATION";
    m[AUTOINDEX] = "AUTOINDEX";
    m[ALLOW_METHODS] = "ALLOW_METHODS";
    m[RETURN] = "RETURN";
    m[INCLUDE] = "INCLUDE";
    m[PATH] = "PATH";
    m[CGI_PATH] = "CGI_PATH";
    m[SERV_NAME] = "SERV_NAME";
    return m;
}

Token::Token(TokenType type, const std::string& lexeme, size_t line)
    : _type(type)
    , _lexeme(lexeme)
    , _line(line)
{
}

TokenType   Token::getType() const { return _type; }

const std::string&    Token::getLexeme() const { return _lexeme; }

const size_t&   Token::getLine() const { return _line; }

std::ostream&   operator<<(std::ostream& os, const Token& token) {
    os << "[" << token.m[token.getType()] << "]:\t" << token.getLexeme()
        << ",\tline: " << token.getLine();
    return os;
}
