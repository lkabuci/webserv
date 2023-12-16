#pragma once

#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

class   MainContext;
class   Context;
class   Directive;

class   Visitor {
public:
    virtual ~Visitor() {}

    virtual void    visitMainContextStmt(MainContext& stmt) = 0;
    virtual void    visitContextStmt(Context& stmt) = 0;
    virtual void    visitDirectiveStmt(Directive& stmt) = 0;
};

#endif
