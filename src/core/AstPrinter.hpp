#pragma once

#ifndef __AST_PRINTER_HPP__
#define __AST_PRINTER_HPP__

#include "Expr.hpp"

class   AstPrinter : public Visitor {
public:
    virtual ~AstPrinter();

    void    print(Expr& stmt);
    void    parenthesize(const std::string& name,
                        std::initializer_list<Expr*> stmts);

    virtual void    visitMainContextExpr(MainContext& stmt);
    virtual void    visitContextExpr(Context& stmt);
    virtual void    visitDirectiveExpr(Directive& stmt);
};

#endif
