#include "Parser.hpp"

Parser::Parser(const std::list<Token>& tokens) : _tokens(tokens), _current(0) {}

std::shared_ptr<Stmt>   Parser::parse() {
    return (statement());
}

std::shared_ptr<Stmt>   Parser::statement() {
    std::shared_ptr<Stmt>   stmt(serverContext());

    while (check(SERVER_CONTEXT)) {
        std::shared_ptr<Stmt>   right(serverContext());
        stmt = std::shared_ptr<Stmt>(new MainContext(stmt, right));
    }
    return stmt;
}

std::shared_ptr<Stmt>   Parser::serverContext() {
    if (!match({SERVER_CONTEXT}))
        throw ParseException(peek(), "Expected a server context.");
    std::shared_ptr<Token>              name(new Token(previous()));
    std::shared_ptr<Context>            stmt(new Context(name));
    std::shared_ptr<Directive>          right(new Directive());
    std::shared_ptr<Stmt>               left;
    std::vector<Directive::Parameter>   params;

    if (!match({LEFT_BRACE}))
        throw ParseException(peek(), "Expect open brace '{'.");
    while (!check(RIGHT_BRACE) && !check(END)) {
        if (isDirectiveKey())
            params.push_back(direcitve());
        if (check(LOCATION_CONTEXT))
            left = std::shared_ptr<Stmt>(new MainContext(left,
                                                        locationContext()));
    }
    consume(RIGHT_BRACE, "Expect end brace.");
    right->add(params);
    stmt->addStmtToRight(right);
    stmt->addStmtToLeft(left);
    return stmt;
}

std::shared_ptr<Stmt>   Parser::locationContext() {
    std::shared_ptr<Token>              name(new Token(peek()));
    std::shared_ptr<Context>            stmt(new Context(name));
    std::shared_ptr<Directive>          right(new Directive());
    std::shared_ptr<Stmt>               left;
    std::vector<Directive::Parameter>   params;

    advance();
    if (!match({PARAMETER})) {
        throw ParseException(peek(), "Expect path.");
    }
    stmt->addParam(peek().getLexeme());
    if (!match({LEFT_BRACE}))
        throw ParseException(peek(), "Expect open brace '{'.");
    while (!check(RIGHT_BRACE) && !check(END)) {
        if (isDirectiveKey())
            params.push_back(direcitve());
        if (check(LOCATION_CONTEXT))
            left = locationContext();
    }
    consume(RIGHT_BRACE, "Expect expression [3].");
    right->add(params);
    stmt->addStmtToRight(right);
    stmt->addStmtToLeft(left);
    return stmt;
}

Directive::Parameter    Parser::direcitve() {
    Directive::Parameter        params;

    do {
        std::string                 key = peek().getLexeme();
        std::vector<std::string>    values;
        advance();
        while (match({PARAMETER})) {
            values.push_back(previous().getLexeme());
        }
        if (!match({SEMICOLON}))
            throw ParseException(peek(), "Expect ';' at end of expression.");
        params[key] = values;
    } while (isDirectiveKey());
    return params;
}

void    Parser::consume(TokenType type, const std::string& message) {
    if (match({type}))
        return;
    throw ParseException(peek(), message);
}

bool    Parser::isDirectiveKey() {
    TokenType   type = peek().getType();

    switch (type) {
        case LISTEN:
        case ROOT:
        case AUTOINDEX:
        case ALLOW_METHODS:
        case SERV_NAME:
        case CLIENT_MAX_BODY_SIZE:
            return true;
        default:
            break;
    }
    return false;
}

bool    Parser::check(TokenType type) {
    return peek().getType() == type;
}

Token&  Parser::peek() {
    std::list<Token>::iterator  it = _tokens.begin();

    std::advance(it, _current);
    return *it;
}

Token&  Parser::previous() {
   std::list<Token>::iterator   it = _tokens.begin();

   std::advance(it, _current - 1);
   return *it;
}

bool    Parser::match(const std::initializer_list<TokenType>& types) {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

void    Parser::advance() {
    if (!isAtEnd())
        ++_current;
}

bool    Parser::isAtEnd() {
    return peek().getType() == END;
}
