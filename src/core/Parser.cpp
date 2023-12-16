#include "Parser.hpp"

Parser::Parser(const std::list<Token>& tokens) : _tokens(tokens), _current(0) {}

std::shared_ptr<Stmt>   Parser::parse() {
    return (statement());
}

std::shared_ptr<Stmt>   Parser::statement() {
    return expression();
}

std::shared_ptr<Stmt>   Parser::expression() {
    std::shared_ptr<Stmt>   expr(serverContext());

    while (!isAtEnd()) {
        std::shared_ptr<Stmt>   right(statement());
        expr = std::shared_ptr<Stmt>(new MainContext(expr, right));
    }
    return expr;
}

std::shared_ptr<Stmt>   Parser::serverContext() {
    consume(SERVER_CONTEXT, "Expected a server context.");
    std::shared_ptr<Token>              name(new Token(previous()));
    std::shared_ptr<Context>            stmt(new Context(name));
    std::shared_ptr<Directive>          left(new Directive());
    std::shared_ptr<Stmt>               right;
    std::vector<Directive::Parameter>   params;

    consume(LEFT_BRACE, "Expect '{' after expression.");
    do {
        if (!isDirectiveKey() && !check(LOCATION_CONTEXT))
            throw ParseException(peek(), "Invalid Expression");
        while (isDirectiveKey()) {
            params.push_back(direcitve());
        }
        if (check(LOCATION_CONTEXT))
            right = std::shared_ptr<Stmt>(new MainContext(right,
                                                        locationContext()));
    } while (!check(RIGHT_BRACE) && !check(END));
    consume(RIGHT_BRACE, "Expect '{' after expression.");
    left->add(params);
    stmt->addStmtToLeft(left);
    stmt->addStmtToRight(right);
    return stmt;
}

std::shared_ptr<Stmt>   Parser::locationContext() {
    std::shared_ptr<Token>              name(new Token(peek()));
    std::shared_ptr<Context>            stmt(new Context(name));
    std::shared_ptr<Directive>          left(new Directive());
    std::vector<Directive::Parameter>   params;

    advance();
    consume(PARAMETER, "Expected parameter.");
    stmt->addParam(previous().getLexeme());
    consume(LEFT_BRACE, "Expect a '{' after expression.");
    while (isDirectiveKey())
        params.push_back(direcitve());
    consume(RIGHT_BRACE, "Expect '}' after expression.");
    left->add(params);
    stmt->addStmtToLeft(left);
    return stmt;
}

Directive::Parameter    Parser::direcitve() {
    Directive::Parameter        params;
    std::string                 key = peek().getLexeme();
    std::vector<std::string>    values;

    advance();
    while (match({PARAMETER})) {
        values.push_back(previous().getLexeme());
    }
    consume(SEMICOLON, "Expect ';' at end of expression.");
    params[key] = values;
    return params;
}

void    Parser::consume(TokenType type, const std::string& message) {
    if (match({type}))
        return;
    throw ParseException(previous(), message);
}

bool    Parser::isDirectiveKey() {
    TokenType   type = peek().getType();

    switch (type) {
        case LISTEN:
        case ROOT:
        case AUTOINDEX:
        case ALLOW_METHODS:
        case SERV_NAME:
        case ERROR_PAGE:
        case INDEX:
        case RETURN:
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
