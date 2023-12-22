#include "Parser.hpp"

//Parser::Parser(const std::list<Token>& tokens)
//    : _tokens(tokens)
//    , _current(0)
//    , _lookahead(_tokens.begin())
//{
//}

//Expr*   Parser::parse() {
//    return expression();
//}

//Expr*   Parser::expression() {
//    Expr*   expr = NULL;

//    try {
//        expr = serverContext();
//        while (!isAtEnd()) {
//            Expr*   right = serverContext();
//            expr = new MainContext(expr, right);
//        }
//    } catch (...) {
//        delete expr;
//        throw;
//    }
//    return expr;
//}

//Expr*   Parser::serverContext() {
//    consume(SERVER_CONTEXT, "Expect a server context.");
//    consume(LEFT_BRACE, "Expect a left brace.");
//    Expr*   expr = NULL;

//    try {
//        expr = serverDirective();
//        while (!isAtEnd() && !check(RIGHT_BRACE)) {
//            Expr*   right = insideBlock();
//            expr = new ServerContext(expr, right);
//        }
//        consume(RIGHT_BRACE, "Expect end brace at end of experssion.");
//    } catch (...) {
//        delete expr;
//        throw;
//    }
//    return expr;
//}

//Expr*   Parser::insideBlock() {
//    if (match(LOCATION_CONTEXT))
//        return locationContext();
//    return serverDirective();
//}

//Expr*   Parser::locationContext() {
//    Expr*   expr = NULL;

//    try {
//        expr = locationParameter();
//        consume(LEFT_BRACE, "Expect left brace after expression.");
//        do {
//            Expr*   right = locationDirective();
//            expr = new LocationContext(expr, right);
//        } while (!check(RIGHT_BRACE) && !check(END));
//        consume(RIGHT_BRACE, "Expect end brace of expression.");
//    } catch (...) {
//        delete expr;
//        throw;
//    }
//    return expr;
//}

//Expr*   Parser::locationParameter() {
//    if (!match(PARAMETER))
//        throw ParseException(peek(), "Expect location path.");
//    std::vector<std::string>    parameter;

//    do {
//        parameter.push_back(previous().getLexeme());
//    } while (match(PARAMETER));
//    return new Parameter(parameter);
//}

//Expr*   Parser::serverDirective() {
//    if (consumeServerDirective()) {
//        Token   opt(previous());
//        Expr*   right = parameter();
//        if (peek().getLine() != previous().getLine() || !match(SEMICOLON)) {
//            delete right;
//            throw ParseException(peek(), "Expect ';' after expression.");
//        }
//        return new Directive(opt, right);
//    }
//    if (!check(LOCATION_CONTEXT) && !check(RIGHT_BRACE))
//        throw ParseException(peek(), "Expect expression.");
//    return NULL;
//}

//Expr*   Parser::locationDirective() {
//    if (consumeLocationDirective()) {
//        Token   opt(previous());
//        Expr*   right = parameter();
//        if (peek().getLine() != previous().getLine() || !match(SEMICOLON)) {
//            delete right;
//            throw ParseException(previous(), "Expect ';' after expression.");
//        }
//        return new Directive(opt, right);
//    }
//    if (!check(RIGHT_BRACE))
//        throw ParseException(peek(), "Expect expression.");
//    return NULL;
//}

//Expr*   Parser::parameter() {
//    std::vector<std::string>    parameters;

//    while (match(PARAMETER)) {
//        parameters.push_back(previous().getLexeme());
//    }
//    return new Parameter(parameters);
//}

//bool    Parser::isServerDirective() {
//    switch (peek().getType()) {
//        case SERVER_NAME:
//        case LISTEN:
//        case ROOT:
//        case INDEX:
//        case CLIENT_MAX_BODY_SIZE:
//            return true;
//        default:
//            break;
//    }
//    return false;
//}

//bool    Parser::consumeServerDirective() {
//    switch (peek().getType()) {
//        case LISTEN:
//        case SERVER_NAME:
//        case ROOT:
//        case CLIENT_MAX_BODY_SIZE:
//        case INDEX:
//        case ERROR_PAGE:
//            advance();
//            return true;
//        default:
//            break;
//    }
//    return false;
//}

//bool    Parser::consumeLocationDirective() {
//    switch (peek().getType()) {
//        case ROOT:
//        case AUTOINDEX:
//        case ALLOW_METHODS:
//        case INDEX:
//        case CLIENT_MAX_BODY_SIZE:
//        case RETURN:
//            advance();
//            return true;
//        default:
//            break;
//    }
//    return false;
//}

//Token  Parser::peek() {
//    return *_lookahead;
//}

//Token  Parser::previous() {
//   std::list<Token>::iterator   it = _tokens.begin();

//    for (int i = 0; i < _current - 1; ++i)
//        ++it;
//   return *it;
//}

//void    Parser::advance() {
//    if (isAtEnd())
//        return;
//    ++_current;
//    ++_lookahead;
//}

//bool    Parser::isAtEnd() {
//    return peek().getType() == END;
//}

//void    Parser::consume(TokenType type, const std::string& message) {
//    if (match(type))
//        return;
//    throw ParseException(previous(), message);
//}

//bool    Parser::isDirectiveKey() {
//    switch (peek().getType()) {
//        case LISTEN:
//        case ROOT:
//        case AUTOINDEX:
//        case ALLOW_METHODS:
//        case SERVER_NAME:
//        case ERROR_PAGE:
//        case INDEX:
//        case RETURN:
//        case CLIENT_MAX_BODY_SIZE:
//            return true;
//        default:
//            break;
//    }
//    return false;
//}

//bool    Parser::check(TokenType type) {
//    return peek().getType() == type;
//}

//bool    Parser::match(TokenType type) {
//    if (peek().getType() == type) {
//        advance();
//        return true;
//    }
//    return false;
//}

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
    consume(SERVER_CONTEXT, "Expect a server context.");
    block();
}

void    Parser::block() {
    consume(LEFT_BRACE, "Expect a left brace after the server context.");
    while (!isAtEnd() && !check(RIGHT_BRACE)) {
        if (matchServerDirective()) {
            parameter();
            if (peek().getLine() != previous().getLine() || !match(SEMICOLON))
                throw ParseException(peek(), "Expect a ';' after statement.");
        } else if (match(LOCATION_CONTEXT)) {
            locationContext();
        } else {
            throw ParseException(peek(), "Invalid statement.");
        }
    }
    consume(RIGHT_BRACE, "Expect end brace '}' after expression.");
}

void    Parser::locationContext() {
    consume(PARAMETER, "Expect a path.");
    std::vector<std::string>    params;

    do {
        params.push_back(previous().getLexeme());
    }   while (match(PARAMETER));
    consume(LEFT_BRACE, "Expect a left brace '{' after statement.");
    if (!matchLocationDirective())
        throw ParseException(peek(), "Expect statement.");
    Token   token;
    do {
        parameter();
        if (peek().getLine() != previous().getLine() || !match(SEMICOLON))
            throw ParseException(peek(), "Expect a ';' after statement.");
    }   while (matchLocationDirective());
    consume(RIGHT_BRACE, "Expect end brace '}' after statement.");
}

void    Parser::parameter() {
    Token   prev = previous();

    if (!check(PARAMETER))
        throw ParseException(peek(), "Expect parameter for the directive.");

    std::vector<std::string>    params;

    while (match(PARAMETER))
        params.push_back(previous().getLexeme());
}

bool    Parser::matchServerDirective() {
    switch (peek().getType()) {
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
    switch (peek().getType()) {
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
    return peek().getType() == type;
}

Token&  Parser::peek() {
    return _token;
}

bool    Parser::isAtEnd() const {
    return _token.getType() == END;
}
