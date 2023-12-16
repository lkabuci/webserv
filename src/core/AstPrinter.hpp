#pragma once

#ifndef __AST_PRINTER_HPP__
#define __AST_PRINTER_HPP__

//#include "Expr.hpp"

//class   AstPrinter : public Visitor {
//public:
//    virtual ~AstPrinter();

//    void    print(Expr& expr);

//    virtual void    visitBinaryExpr(Binary& expr) override;
//    virtual void    visitGroupingExpr(Grouping& expr) override;
//    virtual void    visitStringExpr(String& expr) override;
//    virtual void    visitNumberExpr(Number& expr) override;

//    template<typename T>
//    void    parenthesize(const T& value, std::initializer_list<Expr*> exprs);
//};

#include "Stmt.hpp"

class   AstPrinter : public Visitor {
public:
    virtual ~AstPrinter();

    void    print(Stmt& stmt);
    void    parenthesize(const std::string& name,
                        std::initializer_list<Stmt*> stmts);

    virtual void    visitMainContextStmt(MainContext& stmt);
    virtual void    visitContextStmt(Context& stmt);
    virtual void    visitDirectiveStmt(Directive& stmt);
};

#endif
