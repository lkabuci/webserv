//  For debugging purposes, this class prints the AST in a human-readable format.

#pragma once

#include "ConfigInfo.hpp"
#ifndef __AST_PRINTER_HPP__
#define __AST_PRINTER_HPP__

#include "Expr.hpp"
#include "ServerConfig.hpp"

class   AstPrinter : public Visitor {
public:
    virtual ~AstPrinter();

    void    print(Expr& expr, ConfigInfo& conf);
    void    parenthesize(ConfigInfo& conf, const std::string& name, int n, ...);

    virtual void    visitMainContextExpr(MainContext& expr, ConfigInfo& conf);
    virtual void    visitServerContextExpr(ServerContext& expr,
                                            ConfigInfo& conf);
    virtual void    visitLocationContextExpr(LocationContext& expr,
                                            ConfigInfo& conf);
    virtual void    visitDirectiveExpr(Directive& expr, ConfigInfo& conf);
    virtual void    visitParameterExpr(Parameter& expr, ConfigInfo& conf);
};

#endif
