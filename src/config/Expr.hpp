#pragma once

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "Token.hpp"
#include "ConfigInfo.hpp"
#include "Visitor.hpp"
#include "common.hpp"

class ConfigInfo;

class Expr {
public:
  virtual ~Expr() {}

  virtual void  accept(Visitor& visitor, ConfigInfo& conf) = 0;
};

class   MainContext : public Expr {
public:
    MainContext();
    MainContext(Expr* left, Expr* right);
    MainContext(const MainContext& mainContext);
    virtual ~MainContext();

    MainContext&    operator=(const MainContext& mainContext);

    virtual void    accept(Visitor& visitor, ConfigInfo& conf);

    Expr*   getLeftExpr();
    Expr*   getRightExpr();

private:
    Expr*   _left;
    Expr*   _right;

    void    _swap(MainContext mainContext);
};

class ServerContext : public Expr {
public:
    ServerContext();
    ServerContext(Expr* left, Expr* right);
    ServerContext(const ServerContext& context);
    virtual ~ServerContext();

    ServerContext&    operator=(const ServerContext& context);

    virtual void    accept(Visitor& visitor, ConfigInfo& conf);

    Expr*           getLeftExpr();
    Expr*           getRightExpr();

private:
    Expr*   _left;
    Expr*   _right;

    void    _swap(ServerContext context);
};

class LocationContext : public Expr {
public:
    LocationContext();
    LocationContext(Expr* left, Expr* right);
    LocationContext(const LocationContext& context);
    virtual ~LocationContext();

    LocationContext&    operator=(const LocationContext& context);

    virtual void    accept(Visitor& visitor, ConfigInfo& conf);

    Expr*           getLeftExpr();
    Expr*           getRightExpr();

private:
    Expr*   _left;
    Expr*   _right;

    void    _swap(LocationContext context);
};

class   Directive : public Expr {
public:
    Directive();
    Directive(const Token& opt, Expr* right);
    Directive(const Directive& directive);
    virtual ~Directive();

    Directive&  operator=(const Directive& directive);

    virtual void    accept(Visitor& visitor, ConfigInfo& conf);

    const Token&    getOperator() const;
    Expr*           getRightExpr();

private:
    Token   _opt;
    Expr*   _right;

    void    _swap(Directive directive);
};

class   Parameter : public Expr {
public:
    Parameter();
    Parameter(const std::vector<std::string>& params);
    Parameter(const Parameter& param);
    virtual ~Parameter();

    Parameter&  operator=(const Parameter& param);

    virtual void    accept(Visitor& visitor, ConfigInfo& conf);

    const std::vector<std::string>&  getParams() const;

private:
    std::vector<std::string>    _params;
};

#endif
