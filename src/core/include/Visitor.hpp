#pragma once

#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

class   MainContext;
class   Context;
class   Directive;

class   Visitor {
public:
    virtual ~Visitor() {}

    virtual void    visitMainContextExpr(MainContext& stmt) = 0;
    virtual void    visitContextExpr(Context& stmt) = 0;
    virtual void    visitDirectiveExpr(Directive& stmt) = 0;
};

#endif
