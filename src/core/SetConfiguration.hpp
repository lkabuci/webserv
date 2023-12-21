#pragma once

#include "ConfigInfo.hpp"
#include "Expr.hpp"
#ifndef __SET_CONFIGURATION_HPP__
#define __SET_CONFIGURATION_HPP__

#include "ServerConfig.hpp"
#include "Visitor.hpp"

class   SetConfiguration : public Visitor {
public:
    virtual ~SetConfiguration();

    void    accept(Expr& expr, ConfigInfo& conf);

    virtual void    visitMainContextExpr(MainContext& expr, ConfigInfo& conf);
    virtual void    visitServerContextExpr(ServerContext& expr,
                                            ConfigInfo& conf);
    virtual void    visitLocationContextExpr(LocationContext& expr,
                                            ConfigInfo& conf);
    virtual void    visitDirectiveExpr(Directive& expr, ConfigInfo& conf);
    virtual void    visitParameterExpr(Parameter& expr, ConfigInfo& conf);

    void    visit(ConfigInfo& conf, int n, ...);
};

#endif
