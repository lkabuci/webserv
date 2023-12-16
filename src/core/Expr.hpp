#pragma once

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "common.hpp"
#include "Token.hpp"

class   Visitor;
class   Binary;
class   Grouping;
class   String;
class   Number;

class   Expr {
public:
    virtual ~Expr() {}

    virtual void    accept(Visitor& visitor) = 0;
};

class   Visitor {
public:
    virtual ~Visitor() {}

    virtual void    visitBinaryExpr(Binary& expr) = 0;
    virtual void    visitGroupingExpr(Grouping& expr) = 0;
    virtual void    visitStringExpr(String& expr) = 0;
    virtual void    visitNumberExpr(Number& expr) = 0;
};

class   Binary : public Expr {
public:
    Binary(std::shared_ptr<Expr> left, std::shared_ptr<Token> opt,
            std::shared_ptr<Expr> right);
    virtual ~Binary();

    virtual void    accept(Visitor& visitor) override;

    Expr&   getLeftExpr();
    Token   getOperator();
    Expr&   getRightExpr();

private:
    std::shared_ptr<Expr>   _left;
    std::shared_ptr<Token>  _opt;
    std::shared_ptr<Expr>   _right;
};

class   Grouping : public Expr {
public:
    Grouping(std::shared_ptr<Expr> expr);
    virtual ~Grouping();

    virtual void    accept(Visitor& visitor);

    Expr&   getExpr();

private:
    std::shared_ptr<Expr>   _expr;
};

class   String : public Expr {
public:
    String(size_t value);
    String(const std::string& value);
    virtual ~String();

    virtual void    accept(Visitor& visitor) override;

    const std::string&  getValue() const;

private:
    std::string _value;
};

class   Number : public Expr {
public:
    Number(size_t value);
    virtual ~Number();

    virtual void    accept(Visitor& visitor) override;

    size_t  getValue() const;

private:
    size_t  _value;
};

#endif
