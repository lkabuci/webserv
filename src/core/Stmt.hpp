#pragma once

#ifndef __STMT_HPP__
#define __STMT_HPP__

#include "common.hpp"
#include "Token.hpp"
#include "Visitor.hpp"

class   MainContext;
class   Context;
class   Directive;

class   Stmt {
public:
    virtual ~Stmt() {}

    virtual void    accept(Visitor& visitor) = 0;
};

class   MainContext : public Stmt {
public:
    MainContext() = default;
    MainContext(const std::shared_ptr<Stmt>& left,
                const std::shared_ptr<Stmt>& right);
    virtual ~MainContext();

    virtual void    accept(Visitor& visitor) override;

    Stmt&   getLeftStmt();
    Stmt&   getRightStmt();

private:
    std::shared_ptr<Stmt>   _leftStmt;
    std::shared_ptr<Stmt>   _rightStmt;
};

class   Context : public Stmt {
public:
    Context() = default;
    Context(const std::shared_ptr<Token>& name);
    Context(const std::shared_ptr<Token>& name,
            const std::vector<std::string>& params,
            const std::shared_ptr<Stmt>& left,
            const std::shared_ptr<Stmt>& right);
    virtual ~Context() {}

    virtual void    accept(Visitor& visitor) override;

    Token&                      getName();
    std::vector<std::string>&   getParams();
    Stmt&                       getLeftExpr();
    Stmt&                       getRightStmt();

    void    addParam(const std::string& param);
    void    addStmtToLeft(const std::shared_ptr<Stmt>& left);
    void    addStmtToRight(const std::shared_ptr<Stmt>& right);

private:
    std::shared_ptr<Token>              _name;
    std::vector<std::string>            _params;
    std::shared_ptr<Stmt>               _leftStmt;
    std::shared_ptr<Stmt>               _rightStmt;
};

class   Directive : public Stmt {
public:
    typedef std::map<std::string, std::vector<std::string> >  Parameter;
    Directive();
    Directive(const Parameter& params);
    virtual ~Directive() {}

    virtual void    accept(Visitor& visitor);

    const Parameter&    getParams();

    void    add(std::vector<Parameter>& params);

private:
    Parameter   _params;
};

#endif
