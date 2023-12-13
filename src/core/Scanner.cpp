#include "Scanner.hpp"

std::map<std::string, TokenType>    Scanner::keys = creatKeysMap();

std::map<std::string, TokenType>    Scanner::creatKeysMap() {
    std::map<std::string, TokenType>    m;

    m["server"] = SERVER_BLOCK;
    m["listen"] = LISTEN;
    m["server_name"] = SERV_NAME;
    m["root"] = ROOT;
    m["client_max_body_size"] = CLIENT_MAX_BODY_SIZE;
    m["error_page"] = ERROR_PAGE;
    m["index"] = INDEX;
    m["location"] = LOCATION;
    m["autoindex"] = AUTOINDEX;
    m["allow_methods"] = ALLOW_METHODS;
    m["return"] = RETURN;
    m["include"] = INCLUDE;
    return m;
}

Scanner::Scanner(const std::string& source)
    : _source(source)
    , _start(0)
    , _current(0)
    , _line(1)
    , _length(source.length())
{
}

std::list<Token>    Scanner::scanTokens() {
    while (!isAtEnd()) {
        skipWhiteSpaces();
        _start = _current;
        scanToken();
    }
    return _tokens;
}

void    Scanner::scanToken() {
    char    c = advance();

    switch (c) {
        case '{':   addToken(LEFT_BRACE);   break;
        case '}':   addToken(RIGHT_BRACE);  break;
        case ';':   addToken(SEMICOLON);    break;
        case '\n':  _line++;    break;
        case '#':   skipComment();  break;
        case '\\':  cgi_path(); break;
        default:
            if (std::isdigit(c)) {
                _number();
            } else if (isPath(c)) {
                _path();
            } else if (std::isalpha(c)) {
                _string();
            } else {
                throw SyntaxException(_line, "Unexpected character ", c);
            }
            break;
    }
}

void    Scanner::addToken(TokenType type) {
    std::string text = _source.substr(_start, _current - _start);

    _tokens.push_back(Token(type, text, _line));
}

void    Scanner::_number() {
    while (std::isdigit(peek()))
        advance();
    addToken(NUMBER);
}

void    Scanner::_string() {
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

void    Scanner::_path() {
    while (isValidPathChar(peek()))
        advance();
    addToken(PATH);
}

void    Scanner::cgi_path() {
    advance();
    while (isValidPathChar(peek()))
        advance();
    if (peek() == '$')
        advance();
    addToken(CGI_PATH);
}

void    Scanner::skipComment() {
    while (!isAtEnd() && peek() != '\n')
        advance();
}

bool    Scanner::isAtEnd() const {
    return _current >= _length;
}

bool    Scanner::isStringChar(char c) {
    return !std::isspace(c) && c != ';' && c != '{' && c != '}';
}

bool    Scanner::isPath(char c) {
    return c == '.' || c == '/';
}

bool    Scanner::isValidPathChar(char c) {
    return !(std::isspace(c) && c != ';' && c != '{' && c != '}');
}

void    Scanner::skipWhiteSpaces() {
    while (std::isspace(peek()) && peek() != '\n')
        advance();
}

char    Scanner::peek() {
    if (isAtEnd())
        return '\0';
    return _source.at(_current);
}

char    Scanner::peekNext() {
    if (_current + 1 >= _length)
        return '\0';
    return _source.at(_current + 1);
}

char    Scanner::advance() {
    return _source.at(_current++);
}
