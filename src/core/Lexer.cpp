#include "Lexer.hpp"

std::map<std::string, TokenType>    Lexer::keys = creatKeysMap();

std::map<std::string, TokenType>    Lexer::creatKeysMap() {
    std::map<std::string, TokenType>    m;

    m["server"] = SERVER_CONTEXT;
    m["listen"] = LISTEN;
    m["server_name"] = SERVER_NAME;
    m["root"] = ROOT;
    m["client_max_body_size"] = CLIENT_MAX_BODY_SIZE;
    m["error_page"] = ERROR_PAGE;
    m["index"] = INDEX;
    m["location"] = LOCATION_CONTEXT;
    m["autoindex"] = AUTOINDEX;
    m["allow_methods"] = ALLOW_METHODS;
    m["return"] = RETURN;
    return m;
}

Lexer::Lexer(const std::string& source)
    : _source(source)
    , _start(0)
    , _current(0)
    , _line(1)
    , _length(source.length())
{
}

std::list<Token>    Lexer::scanTokens() {
    while (!isAtEnd()) {
        skipWhiteSpaces();
        _start = _current;
        scanToken();
    }
    _tokens.push_back(Token(END, "", _line));
    return _tokens;
}

void    Lexer::scanToken() {
    char    c = advance();

    switch (c) {
        case '{':   addToken(LEFT_BRACE);   break;
        case '}':   addToken(RIGHT_BRACE);  break;
        case ';':   addToken(SEMICOLON);    break;
        case '\n':  _line++;                break;
        case '#':   skipComment();          break;
        case '"':
        case '\'':
            quotes(c);
            break;
        default:    _string();              break;
    }
}

void    Lexer::quotes(char c) {
    advance();
    while (peek() != c && peek() != '\n')
        advance();
    if (peek() == '\n')
        throw SyntaxException(_line, "Unterminated string");
    advance();
    std::string text = _source.substr(_start + 1, _current - _start - 2);
    _tokens.push_back(Token(PARAMETER, text, _line));
}

void    Lexer::addToken(TokenType type) {
    std::string text = _source.substr(_start, _current - _start);

    _tokens.push_back(Token(type, text, _line));
}

void    Lexer::_string() {
    while (isStringChar(peek()))
        advance();
    std::string text = _source.substr(_start, _current - _start);
    TokenType   type;

    try {
        type = keys.at(text);
    } catch (const std::exception& e) {
        type = PARAMETER;
    }
    addToken(type);
}

void    Lexer::skipComment() {
    while (!isAtEnd() && peek() != '\n')
        advance();
}

bool    Lexer::isAtEnd() const {
    return _current >= _length;
}

bool    Lexer::isStringChar(char c) {
    return !std::isspace(c) && c != ';' && c != '{' && c != '}' && c != '#';
}

bool    Lexer::isPath(char c) {
    return c == '.' || c == '/';
}

bool    Lexer::isValidPathChar(char c) {
    return !(std::isspace(c) && c != ';' && c != '{' && c != '}' && c != '#');
}

void    Lexer::skipWhiteSpaces() {
    while (std::isspace(peek()) && peek() != '\n')
        advance();
}

char    Lexer::peek() {
    if (isAtEnd())
        return '\0';
    return _source.at(_current);
}

char    Lexer::peekNext() {
    if (_current + 1 >= _length)
        return '\0';
    return _source.at(_current + 1);
}

char    Lexer::advance() {
    if (isAtEnd())
        return '\0';
    return _source.at(_current++);
}
