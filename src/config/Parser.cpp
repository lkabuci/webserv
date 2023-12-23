#include "Parser.hpp"
#include "Env.hpp"
#include "Token.hpp"
#include "TokenType.hpp"

Parser::Parser(const std::string& source)
    : _lexer(source),
    , _token(_lexer.scan())
    , _prev(_token)
{
}

void    Parser::parse() {
    statement();
}

void    Parser::statement() {
    serverContext();

    while (!isAtEnd()) {
        serverContext();
    }
}

void    Parser::serverContext() {
    consume(SERVER, "Expect a server context.");
    block();
}

void    Parser::block() {
    consume(LEFT_BRACE, "Expect a left brace after the server context.");
    Env::create(SERVER);
    while (!isAtEnd() && !check(RIGHT_BRACE)) {
        if (matchServerDirective()) {
            parameter(SERVER);
        } else if (match(LOCATION)) {
            locationContext();
        } else {
            throw ParseException(peek(), "Invalid statement.");
        }
    }
    consume(RIGHT_BRACE, "Expect end brace '}' after expression.");
    Env::add(SERVER);
}

void    Parser::locationContext() {
    consume(PARAMETER, "Expect a path.");
    Token                       prev = previous();
    std::vector<std::string>    params;

    Env::create(LOCATION);
    do {
        params.push_back(previous().lexeme());
    }   while (match(PARAMETER));
    Env::put(params, prev);
    consume(LEFT_BRACE, "Expect a left brace '{' after statement.");
    Token   token;
    while (matchLocationDirective())
        parameter(LOCATION);
    consume(RIGHT_BRACE, "Expect end brace '}' after statement.");
    Env::add(LOCATION);
}

void    Parser::parameter(TokenType type) {
    Token   prev = previous();

    if (!check(PARAMETER))
        throw ParseException(peek(), "Expect parameter for the directive.");

    std::vector<std::string>    params;

    while (match(PARAMETER))
        params.push_back(previous().lexeme());
    if (peek().line() != previous().line() || !match(SEMICOLON))
        throw ParseException(peek(), "Expect a ';' after statement.");
    if (type == SERVER) {
        Env::put(params, prev);
    } else {
        Env::put(params, prev);
    }
}

bool    Parser::matchServerDirective() {
    switch (peek().type()) {
        case LISTEN:
        case SERVER_NAME:
        case CLIENT_MAX_BODY_SIZE:
        case ROOT:
        case INDEX:
        case ALLOW_METHODS:
        case ERROR_PAGE:
            advance();
            return true;
        default:
            break;
    }
    return false;
}

bool    Parser::matchLocationDirective() {
    switch (peek().type()) {
        case AUTOINDEX:
        case RETURN:
        case ALLOW_METHODS:
        case ROOT:
        case INDEX:
        case ERROR_PAGE:
        case CLIENT_MAX_BODY_SIZE:
            advance();
            return true;
        default:
            break;
    }
    return false;
}

void    Parser::consume(TokenType type, const std::string& message) {
    if (match(type))
        return;
    throw ParseException(_prev, message);
}

bool    Parser::match(TokenType type) {
    if (!check(type))
        return false;
    advance();
    return true;
}

Token&  Parser::previous() { return _prev; }

void    Parser::advance() {
    if (isAtEnd())
        return;
    _prev = _token;
    _token = _lexer.scan();
}

bool    Parser::check(TokenType type) {
    return peek().type() == type;
}

Token&  Parser::peek() {
    return _token;
}

bool    Parser::isAtEnd() const {
    return _token.type() == END;
}
