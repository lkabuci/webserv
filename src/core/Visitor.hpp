#pragma once

#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

class   MainContext;
class   Context;
class   ServerContext;
class   LocationContext;
class   Directive;
class   Parameter;
class   HttpConfig;

class   Visitor {
public:
    virtual ~Visitor() {}

    virtual void    visitMainContextExpr(MainContext& expr) = 0;
    virtual void    visitServerContextExpr(ServerContext& expr) = 0;
    virtual void    visitLocationContextExpr(LocationContext& expr) = 0;
    virtual void    visitDirectiveExpr(Directive& expr) = 0;
    virtual void    visitParameterExpr(Parameter& expr) = 0;
};

#endif
