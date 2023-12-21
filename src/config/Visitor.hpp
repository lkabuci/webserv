#pragma once

#include "ConfigInfo.hpp"
#include "ServerConfig.hpp"
#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

class   MainContext;
class   Context;
class   ServerContext;
class   LocationContext;
class   Directive;
class   Parameter;
class   ConfigInfo;

class   Visitor {
public:
    virtual ~Visitor() {}

    virtual void    visitMainContextExpr(MainContext& expr,
                                        ConfigInfo& conf) = 0;
    virtual void    visitServerContextExpr(ServerContext& expr,
                                        ConfigInfo& conf) = 0;
    virtual void    visitLocationContextExpr(LocationContext& expr,
                                        ConfigInfo& conf) = 0;
    virtual void    visitDirectiveExpr(Directive& expr, ConfigInfo& conf) = 0;
    virtual void    visitParameterExpr(Parameter& expr, ConfigInfo& conf) = 0;
};

#endif
