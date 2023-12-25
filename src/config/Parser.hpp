#pragma once

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "Lexer.hpp"
#include "ParseException.hpp"

class Stmt;

class Parser {
  public:
    Parser(const std::string& source);

    void parse();

    // private:
    Parser(const Parser&);
    Parser& operator=(const Parser&);

    Lexer _lexer;
    Token _token;
    Token _prev;

    void statement();
    void serverContext();
    void block();
    void locationContext();
    void parameter(TokenType type);
    void serverDirective();

    bool matchLocationDirective();
    bool matchServerDirective();
    bool check(TokenType type);
    void advance();
    Token& peek();
    Token& previous();
    bool match(TokenType type);
    void consume(TokenType type, const std::string& message);
    bool isAtEnd() const;
};

#endif
