#pragma once

#ifndef __INTERPRET_HPP__
#define __INTERPRET_HPP__

#include "Expr.hpp"

class   Interpret : public Visitor {
public:
    virtual ~Interpret();

    void    interpret(std::list<std::shared_ptr<Expr> > exprs);

    virtual void    visitBinaryExpr(Binary& expr) override;
    virtual void    visitGroupingExpr(Grouping& expr) override;
    virtual void    visitStringExpr(String& expr) override;
    virtual void    visitNumberExpr(Number& expr) override;

    void    evaluate(Expr& expr);
};

#endif
