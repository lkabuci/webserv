#pragma once

#ifndef __AST_PRINTER_HPP__
#define __AST_PRINTER_HPP__

#include "Expr.hpp"

class   AstPrinter : public Visitor {
public:
    virtual ~AstPrinter();

    void    print(Expr& expr);
    void    parenthesize(const std::string& name, int n, ...);

    virtual void    visitMainContextExpr(MainContext& expr);
    virtual void    visitServerContextExpr(ServerContext& expr);
    virtual void    visitLocationContextExpr(LocationContext& expr);
    virtual void    visitDirectiveExpr(Directive& expr);
    virtual void    visitParameterExpr(Parameter& expr);
};

#endif
