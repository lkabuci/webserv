#pragma once

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "ParseException.hpp"
//#include "Expr.hpp"
#include <stdarg.h>
#include "Lexer.hpp"

class   Stmt;

class   Parser {
public:
    //Parser(const std::list<Token>& tokens);
    Parser(const std::string& source);

    void    parse();

private:
    Parser(const Parser&);
    Parser& operator=(const Parser&);

    //std::list<Token>            _tokens;
    //int                         _current;
    //std::list<Token>::iterator  _lookahead;

    //Expr*   expression();
    //Expr*   serverContext();
    //Expr*   locationContext();
    //Expr*   serverDirective();
    //Expr*   locationDirective();
    //Expr*   insideBlock();
    //Expr*   parameter();
    //Expr*   locationParameter();

    //bool    check(TokenType type);
    //Token  peek();
    ////Token  peekNext();
    //bool    match(TokenType type);
    //void    advance();
    //Token  previous();
    //bool    isAtEnd();
    //bool    isDirectiveKey();
    //void    consume(TokenType type, const std::string& message);
    //bool    isServerDirective();
    //bool    consumeServerDirective();
    //bool    consumeLocationDirective();

    Lexer   _lexer;
    Token   _token;
    Token   _prev;

    void    statement();
    void    serverContext();
    void    block();
    void    locationContext();
    void    parameter();
    void    serverDirective();

    bool    matchLocationDirective();
    bool    matchServerDirective();
    bool    check(TokenType type);
    void    advance();
    Token&  peek();
    Token&  previous();
    bool    match(TokenType type);
    void    consume(TokenType type, const std::string& message);
    bool    isAtEnd() const;
};

#endif
