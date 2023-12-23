#include "Parser.hpp"

Parser::Parser(const std::string& source) : _lexer(source) {
    _token = _lexer.scan();
    _prev = _token;
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
    std::cout << "------> EXIT FROM SERVER BLOCK\n";
}

void    Parser::block() {
    consume(LEFT_BRACE, "Expect a left brace after the server context.");
    std::cout << "------> SERVER BLOCK\n";
    while (!isAtEnd() && !check(RIGHT_BRACE)) {
        if (matchServerDirective()) {
            parameter(SERVER);
            if (peek().line() != previous().line() || !match(SEMICOLON))
                throw ParseException(peek(), "Expect a ';' after statement.");
        } else if (match(LOCATION)) {
            locationContext();
        } else {
            throw ParseException(peek(), "Invalid statement.");
        }
    }
    consume(RIGHT_BRACE, "Expect end brace '}' after expression.");
}

void    Parser::locationContext() {
    consume(PARAMETER, "Expect a path.");
    std::cout << "\n\t------> LOCATION BLOCK\n";
    std::vector<std::string>    params;

    do {
        params.push_back(previous().lexeme());
    }   while (match(PARAMETER));
    std::cout << "\t\tADD ";
    for (size_t i = 0; i < params.size(); ++i)
        std::cout << " " << params[i];
    std::cout << ". To the parameter of location\n";
    consume(LEFT_BRACE, "Expect a left brace '{' after statement.");
    if (!matchLocationDirective())
        throw ParseException(peek(), "Expect statement.");
    Token   token;
    do {
        parameter(LOCATION);
        if (peek().line() != previous().line() || !match(SEMICOLON))
            throw ParseException(peek(), "Expect a ';' after statement.");
    }   while (matchLocationDirective());
    consume(RIGHT_BRACE, "Expect end brace '}' after statement.");
    std::cout << "\t------> EXIT FROM LOCATION BLOCK\n\n";
}

void    Parser::parameter(TokenType type) {
    Token   prev = previous();

    if (!check(PARAMETER))
        throw ParseException(peek(), "Expect parameter for the directive.");

    std::vector<std::string>    params;

    while (match(PARAMETER))
        params.push_back(previous().lexeme());
    if (type == SERVER) {
        std::cout << "\tADD " << prev.lexeme() << ":";
        for (size_t i = 0; i < params.size(); ++i)
            std::cout << " " << params[i];
        std::cout << ". To the server block\n";
    } else {
        std::cout << "\t\tADD " << prev.lexeme() << ":";
        for (size_t i = 0; i < params.size(); ++i)
            std::cout << " " << params[i];
        std::cout << ". To the location block\n";
    }
}

bool    Parser::matchServerDirective() {
    switch (peek().type()) {
        case LISTEN:
        case SERVER_NAME:
        case CLIENT_MAX_BODY_SIZE:
        case ROOT:
        case INDEX:
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
