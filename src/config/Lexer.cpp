#include "Lexer.hpp"
#include "SyntaxException.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include <cctype>
#include <ratio>
#include <string>

//std::map<std::string, TokenType>    Lexer::keys = creatKeysMap();

//std::map<std::string, TokenType>    Lexer::creatKeysMap() {
//    std::map<std::string, TokenType>    m;

//    m["server"] = SERVER_CONTEXT;
//    m["listen"] = LISTEN;
//    m["server_name"] = SERVER_NAME;
//    m["root"] = ROOT;
//    m["client_max_body_size"] = CLIENT_MAX_BODY_SIZE;
//    m["error_page"] = ERROR_PAGE;
//    m["index"] = INDEX;
//    m["location"] = LOCATION_CONTEXT;
//    m["autoindex"] = AUTOINDEX;
//    m["allow_methods"] = ALLOW_METHODS;
//    m["return"] = RETURN;
//    return m;
//}

//Lexer::Lexer(const std::string& source)
//    : _source(source)
//    , _start(0)
//    , _current(0)
//    , _line(1)
//    , _length(source.length())
//{
//}

//std::list<Token>    Lexer::scanTokens() {
//    while (!isAtEnd()) {
//        skipWhiteSpaces();
//        _start = _current;
//        scanToken();
//    }
//    _tokens.push_back(Token(END, "", _line));
//    return _tokens;
//}

//void    Lexer::scanToken() {
//    char    c = advance();

//    switch (c) {
//        case '\0':  break;
//        case '{':   addToken(LEFT_BRACE);   break;
//        case '}':   addToken(RIGHT_BRACE);  break;
//        case ';':   addToken(SEMICOLON);    break;
//        case '\n':  _line++;                break;
//        case '#':   skipComment();          break;
//        case '"':
//        case '\'':
//            quotes(c);
//            break;
//        default:    _string();              break;
//    }
//}

//void    Lexer::quotes(char c) {
//    advance();
//    while (!isAtEnd() && peek() != c && peek() != '\n')
//        advance();
//    if (isAtEnd() || peek() == '\n')
//        throw SyntaxException(_line, "Unterminated string");
//    advance();
//    std::string text = _source.substr(_start + 1, _current - _start - 2);
//    _tokens.push_back(Token(PARAMETER, text, _line));
//}

//void    Lexer::addToken(TokenType type) {
//    std::string text = _source.substr(_start, _current - _start);

//    _tokens.push_back(Token(type, text, _line));
//}

//void    Lexer::_string() {
//    while (isStringChar(peek()))
//        advance();
//    std::string text = _source.substr(_start, _current - _start);
//    TokenType   type;

//    try {
//        type = keys.at(text);
//    } catch (const std::exception& e) {
//        type = PARAMETER;
//    }
//    addToken(type);
//}

//void    Lexer::skipComment() {
//    while (!isAtEnd() && peek() != '\n')
//        advance();
//}

//bool    Lexer::isAtEnd() const {
//    return _current >= _length;
//}

//bool    Lexer::isStringChar(char c) {
//    return !std::isspace(c) && c != ';' && c != '{' && c != '}' && c != '#'
//            && !isAtEnd();
//}

//void    Lexer::skipWhiteSpaces() {
//    while (std::isspace(peek()) && peek() != '\n')
//        advance();
//}

//char    Lexer::peek() {
//    if (isAtEnd())
//        return '\0';
//    return _source.at(_current);
//}

//char    Lexer::peekNext() {
//    if (_current + 1 >= _length)
//        return '\0';
//    return _source.at(_current + 1);
//}

//char    Lexer::advance() {
//    if (isAtEnd())
//        return '\0';
//    return _source.at(_current++);
//}

std::map<std::string, TokenType>    Lexer::keywords;
std::map<TokenType, std::string>    Lexer::keywordsValues;

Lexer::Lexer(const std::string& source)
    : _source(source)
    , _length(source.length())
    , _start(0)
    , _current(0)
    , _line(1)
{
    reserve();
}

Lexer::~Lexer() {}

Token   Lexer::scan() {
    //if (isAtEnd())
    //    return Token(END, "", _line);
    return scanToken();
    //return _token;
}

Token   Lexer::scanToken() {
    char    c;

    while (!isAtEnd()) {
        _start = _current;
        switch ((c = advance())) {
            case ' ':
            case '\t':
            case '\r':  break;
            case '#':   skipComment();  break;
            case '\n':  _line++;        break;
            case '{':   setToken(LEFT_BRACE);   return _token;
            case '}':   setToken(RIGHT_BRACE);  return _token;
            case ';':   setToken(SEMICOLON);    return _token;
            case '\'':
            case '"':   _string(c);      return _token;
            default:    _parameter();   return _token;
        }
    }
    return Token(END, "", _line);
}

void    Lexer::setToken(TokenType type) {
    std::string text = _source.substr(_start, _current - _start);

    _token = Token(type, text, _line);
}

void    Lexer::setToken(TokenType type, const std::string& text) {
    _token = Token(type, text, _line);
}

void    Lexer::_parameter() {
    while (!isAtEnd() && isParameterChar(peek()))
        advance();

    std::string text = _source.substr(_start, _current - _start);
    TokenType   type;

    if (keywords.find(text) != keywords.end())
        type = keywords[text];
    else
        type = PARAMETER;
    setToken(type, text);
}

void    Lexer::_string(char c) {
    advance();
    while (!isAtEnd() && peek() != c && peek() != '\n')
        advance();
    if (peek() != c)
        throw SyntaxException(_line, "Unterminated string.");
    advance();
    std::string text = _source.substr(_start + 1, _current - _start - 2);
    setToken(PARAMETER, text);
}

void    Lexer::skipComment() {
    while (!isAtEnd() && peek() != '\n')
        advance();
}

void    Lexer::skipWhiteSpaces() {
    while (!isAtEnd() && std::isspace(peek()))
        advance();
}

bool    Lexer::isParameterChar(char c) {
    return !std::isspace(c) && c != '{' && c != '}' && c != '#' && c != ';';
}

char    Lexer::advance() {
    if (isAtEnd())
        return '\0';
    return _source.at(_current++);
}

char    Lexer::peek() {
    if (isAtEnd())
        return '\0';
    return _source.at(_current);
}

bool    Lexer::isAtEnd() const {
    return _current >= _length;
}

void    Lexer::reserve() {
    keywords["server"] = SERVER;
    keywords["location"] = LOCATION;
    keywords["listen"] = LISTEN;
    keywords["server_name"] = SERVER_NAME;
    keywords["client_max_body_size"] = CLIENT_MAX_BODY_SIZE;
    keywords["error_page"] = ERROR_PAGE;
    keywords["root"] = ROOT;
    keywords["index"] = INDEX;
    keywords["autoindex"] = AUTOINDEX;
    keywords["return"] = RETURN;
    keywords["allow_methods"] = ALLOW_METHODS;
    keywords["end"] = END;

    keywordsValues[SERVER] = "server";
    keywordsValues[LOCATION] = "location";
    keywordsValues[LISTEN] = "listen";
    keywordsValues[SERVER_NAME] = "server_name";
    keywordsValues[CLIENT_MAX_BODY_SIZE] = "client_max_body_size";
    keywordsValues[ERROR_PAGE] = "error_page";
    keywordsValues[ROOT] = "root";
    keywordsValues[INDEX] = "index";
    keywordsValues[AUTOINDEX] = "autoindex";
    keywordsValues[RETURN] = "return";
    keywordsValues[ALLOW_METHODS] = "allow_methods";
    keywordsValues[LEFT_BRACE] = "left_brace";
    keywordsValues[RIGHT_BRACE] = "right_brace";
    keywordsValues[SEMICOLON] = "semicolon";
    keywordsValues[PARAMETER] = "parameter";
    keywordsValues[END] = "END";
}
