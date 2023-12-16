#pragma once

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "ParseException.hpp"
#include "Stmt.hpp"

//class   Parser {
//public:
//    Parser(std::list<Token>& tokens);
//    Parser(const Parser&) = delete;
//    Parser& operator=(const Parser&) = delete;

//    std::list<std::shared_ptr<Expr> >    parse();

//private:
//    std::list<Token>    _tokens;
//    size_t              _current;

//    std::shared_ptr<Expr>   expression();
//    std::shared_ptr<Expr>   statement();
//    std::shared_ptr<Expr>   directive();
//    std::shared_ptr<Expr>   identifier();
//    std::shared_ptr<Expr>   params();

//    bool    match(std::initializer_list<TokenType> types);
//    bool    isAtEnd();
//    bool    check(TokenType type);
//    Token&  peek();
//    void    advance();
//    Token&  previous();
//    void    consume(TokenType type, const std::string& message);
//};

class   Parser {
public:
    Parser(const std::list<Token>& tokens);
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;

    std::shared_ptr<Stmt>   parse();

private:
    std::list<Token>    _tokens;
    size_t              _current;

    std::shared_ptr<Stmt>   statement();
    std::shared_ptr<Stmt>   serverContext();
    std::shared_ptr<Stmt>   block();
    Directive::Parameter    direcitve();
    std::shared_ptr<Stmt>   locationContext();

    bool    check(TokenType type);
    Token&  peek();
    bool    match(const std::initializer_list<TokenType>& types);
    void    advance();
    Token&  previous();
    bool    isAtEnd();
    bool    isDirectiveKey();
    void    consume(TokenType type, const std::string& message);
};

#endif
