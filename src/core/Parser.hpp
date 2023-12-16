#pragma once

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "ParseException.hpp"
#include "Expr.hpp"

class   Parser {
public:
    Parser(const std::list<Token>& tokens);
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;

    std::shared_ptr<Expr>   parse();

private:
    std::list<Token>    _tokens;
    size_t              _current;

    std::shared_ptr<Expr>   statement();
    std::shared_ptr<Expr>   expression();
    std::shared_ptr<Expr>   serverContext();
    std::shared_ptr<Expr>   block();
    Directive::Parameter    direcitve();
    std::shared_ptr<Expr>   locationContext();

    bool    check(TokenType type);
    Token&  peek();
    bool    match(const std::initializer_list<TokenType>& types);
    void    advance();
    Token&  previous();
    bool    isAtEnd();
    bool    isDirectiveKey();
    void    consume(TokenType type, const std::string& message);
    bool    consumeDirective();
    bool    isInvalidToken();
};

#endif
