#include "Parser.hpp"

Parser::Parser(const std::list<Token>& tokens)
    : _tokens(tokens)
    , _current(0)
    , _itCurrent(_tokens.begin())
{
}

Expr*   Parser::parse() {
    return statement();
}

Expr*   Parser::statement() {
    try {
        return expression();
    } catch (...) {
        throw;
    }
}

Expr*   Parser::expression() {
    Expr*   expr = NULL;

    try {
        expr = serverContext();
        while (!isAtEnd()) {
            Expr*   right(statement());
            expr = new MainContext(expr, right);
        }
    } catch (...) {
        delete expr;
        throw;
    }
    return expr;
}

Expr*   Parser::serverContext() {
    if (!match(1, SERVER_CONTEXT))
        throw ParseException(peek(), "Expected a server context.");
    Token                               name(previous());
    consume(LEFT_BRACE, "Expect '{' after expression.");
    Directive*                          left = new Directive();
    Expr*                               right = NULL;
    std::vector<Directive::Parameter>   params;

    try {
        do {
            if (!isDirectiveKey() && !check(LOCATION_CONTEXT))
                throw ParseException(peek(), "Invalid Expression");
            while (consumeDirective()) {
                params.push_back(direcitve());
            }
            if (match(1, LOCATION_CONTEXT))
                right = new MainContext(right, locationContext());
        } while (!check(RIGHT_BRACE) && !check(END));
        consume(RIGHT_BRACE, "Expect '}' after expression.");
    } catch (...) {
        delete left;
        delete right;
        throw;
    }
    Context*    stmt = new Context(name);

    left->add(params);
    stmt->addExprToLeft(left);
    stmt->addExprToRight(right);
    return stmt;
}

Expr*   Parser::locationContext() {
    Token   name(previous());

    try {
        consume(PARAMETER, "Expected parameter.");

        std::string                         path(previous().getLexeme());
        std::vector<Directive::Parameter>   params;

        consume(LEFT_BRACE, "Expect a '{' after expression.");
        if (!isDirectiveKey())
            throw ParseException(previous(), "Expect directive.");
        while (consumeDirective())
            params.push_back(direcitve());

        consume(RIGHT_BRACE, "Expect '}' after expression.");
        Context*    stmt(new Context(name));
        Directive*  left(new Directive());
        stmt->addParam(path);
        left->add(params);
        stmt->addExprToLeft(left);
        return stmt;
    } catch (...) {
        throw;
    }
}

Directive::Parameter    Parser::direcitve() {
    std::string                 key = previous().getLexeme();
    Directive::Parameter        params;
    std::vector<std::string>    values;

    while (match(1, PARAMETER)) {
        values.push_back(previous().getLexeme());
    }
    consume(SEMICOLON, "Expect ';' at end of expression.");
    params[key] = values;
    return params;
}

void    Parser::consume(TokenType type, const std::string& message) {
    if (match(1, type))
        return;
    throw ParseException(previous(), message);
}

bool    Parser::isDirectiveKey() {
    switch (peek().getType()) {
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
    return *_itCurrent;
}

Token&  Parser::previous() {
   std::list<Token>::iterator   it = _tokens.begin();

    for (size_t i = 0; i < _current - 1; ++i)
        ++it;
   return *it;
}

bool    Parser::consumeDirective() {
    if (!isDirectiveKey())
        return false;
    advance();
    return true;
}

bool    Parser::match(int n, ...) {
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; ++i) {
        if (check(static_cast<TokenType>(va_arg(ap, int)))) {
            advance();
            va_end(ap);
            return true;
        }
    }
    va_end(ap);
    return false;
}

void    Parser::advance() {
    if (isAtEnd())
        return;
    ++_current;
    ++_itCurrent;
}

bool    Parser::isAtEnd() {
    return peek().getType() == END;
}
