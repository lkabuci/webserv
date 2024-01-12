#include "Scanner.hpp"

Scanner::Scanner() {}

Scanner::Scanner(const std::string& source)
    : _source(source), _start(0), _current(0), _length(_source.length()) {}

Scanner::Scanner(const Scanner& scanner)
    : _token(scanner._token), _source(scanner._source), _start(scanner._start),
      _current(scanner._current), _length(scanner._length) {}

Scanner& Scanner::operator=(const Scanner& scanner) {
    if (this == &scanner)
        return *this;
    _token = scanner._token;
    _source = scanner._source;
    _start = scanner._start;
    _current = scanner._current;
    _length = scanner._length;
    return *this;
}

Token Scanner::get_next_token() {
    char c;

    while (!is_at_end()) {
        _start = _current;
        switch ((c = advance())) {
        case '\0':
            break;
        case '\r':
            if (match('\n'))
                return Token(CR_LF, "\r\n");
            return Token(CR_, "\r");
        case '(':
            comment();
            break;
        case ')':
            return Token(RIGHT_PAREN, ")");
        case '<':
            return Token(LEFT_ANGLE, "<");
        case '>':
            return Token(RIGHT_ANGLE, ">");
        case '@':
            return Token(AT_SIGN, "@");
        case ',':
            return Token(COMMA, ",");
        case ':':
            return Token(COLON, ":");
        case ';':
            return Token(SEMICOLON, ";");
        case '\\':
            return Token(BACK_SLASH, "\\");
        case '"':
            quoted_string();
            return _token;
        case '/':
            return Token(SLASH, "/");
        case '[':
            return Token(LEFT_BRACKET, "[");
        case ']':
            return Token(RIGHT_BRACKET, "]");
        case '?':
            return Token(QUESTION_MARK, "?");
        case '=':
            return Token(EQUAL, "=");
        case '{':
            return Token(LEFT_BRACE, "{");
        case '}':
            return Token(RIGHT_BRACE, "}");
        case ' ':
            return Token(SP, " ");
        case '\t':
            return Token(HT, "\t");
        default:
            token();
            return _token;
        }
    }
    return Token(END, "");
}

void Scanner::token() {
    while (!is_at_end() && !is_separator(peek()))
        advance();
    set_token(TOKEN);
}

void Scanner::quoted_string() {
    while (!is_at_end() && !check('"'))
        advance();
    std::string lexeme = _source.substr(_start + 1, _current - _start - 1);
    _token = Token(QUOTED_STRING, lexeme);
}

void Scanner::comment() {
    while (!is_at_end() && !check(')'))
        advance();
    consume(')', "unterminated comment.");
}

void Scanner::set_token(const TokenType& type) {
    std::string lexeme = _source.substr(_start, _current - _start);

    _token = Token(type, lexeme);
}

char Scanner::peek() {
    return _source.at(_current);
}

char Scanner::peek_next() {
    if (_current + 1 >= _length)
        return '\0';
    return _source.at(_current + 1);
}

char Scanner::advance() {
    if (is_at_end())
        return '\0';
    return _source.at(_current++);
}

void Scanner::consume(char c, const char* message) {
    if (!match(c))
        throw std::runtime_error(message);
}

bool Scanner::check(char c) {
    if (is_at_end())
        return '\0';
    return _source.at(_current) == c;
}

bool Scanner::match(char expected) {
    if (_source.at(_current) != expected)
        return false;
    ++_current;
    return true;
}

bool Scanner::is_at_end() const {
    return _current >= _length;
}

bool Scanner::is_separator(char c) {
    switch (c) {
    case '(':
    case ')':
    case '<':
    case '>':
    case '@':
    case ',':
    case ';':
    case ':':
    case '\\':
    case '"':
    case '/':
    case '[':
    case ']':
    case '?':
    case '=':
    case ' ':
    case '\t':
        return true;
    case '\r':
        if (peek_next() == '\n')
            return true;
    default:
        break;
    }
    return false;
}
