#pragma once

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "Token.hpp"
#include "Visitor.hpp"
#include "common.hpp"

class HttpConfig;

class Expr {
public:
  virtual ~Expr() {}

  virtual void  accept(Visitor& visitor) = 0;
};

class   MainContext : public Expr {
public:
    MainContext();
    MainContext(Expr* left, Expr* right);
    MainContext(const MainContext& mainContext);
    virtual ~MainContext();

    MainContext&    operator=(const MainContext& mainContext);

    virtual void    accept(Visitor& visitor);

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
    //ServerContext(Expr* left, const Token& opt, Expr* right);
    ServerContext(Expr* left, Expr* right);
    ServerContext(const ServerContext& context);
    virtual ~ServerContext();

    ServerContext&    operator=(const ServerContext& context);

    virtual void    accept(Visitor& visitor);

    Expr*           getLeftExpr();
    //const Token&    getOperator() const;
    Expr*           getRightExpr();

private:
    Expr*   _left;
    //Token   _opt;
    Expr*   _right;

    void    _swap(ServerContext context);
};

class LocationContext : public Expr {
public:
    LocationContext();
    LocationContext(Expr* left, Expr* right);
    //LocationContext(Expr* left, const Token& opt, Expr* right);
    LocationContext(const LocationContext& context);
    virtual ~LocationContext();

    LocationContext&    operator=(const LocationContext& context);

    virtual void    accept(Visitor& visitor);

    Expr*           getLeftExpr();
    //const Token&    getOperator() const;
    Expr*           getRightExpr();

private:
    Expr*   _left;
    //Token   _opt;
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

    virtual void    accept(Visitor& visitor);

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

    virtual void    accept(Visitor& visitor);

    const std::vector<std::string>&  getParams() const;

private:
    std::vector<std::string>    _params;
};

//class MainContext : public Expr {
//  public:
//    MainContext();
//    MainContext(Expr* left, Expr* right);
//    MainContext(const MainContext& mc);
//    virtual ~MainContext();

//    MainContext&  operator=(const MainContext& mc);

//    virtual void accept(Visitor& visitor, HttpConfig& svconf);

//    Expr* getLeftExpr();
//    Expr* getRightExpr();

//  private:
//    Expr* _leftExpr;
//    Expr* _rightExpr;

//    void  swap(MainContext mc);
//};

//class Context : public Expr {
//  public:
//    Context();
//    Context(const Token& name);
//    Context(const Token& name, const std::vector<std::string>& params,
//            Expr* left, Expr* right);
//    Context(const Context& c);
//    virtual ~Context();

//    Context&  operator=(const Context& c);

//    virtual void accept(Visitor& visitor, HttpConfig& svconf);

//    Token& getName();
//    std::vector<std::string>& getParams();
//    Expr* getLeftExpr();
//    Expr* getRightExpr();

//    void addParam(const std::string& param);
//    void addExprToLeft(Expr* left);
//    void addExprToRight(Expr* right);

//  private:
//    Token                     _name;
//    std::vector<std::string>  _params;
//    Expr*                     _leftExpr;
//    Expr*                     _rightExpr;
//};

//class LocationContext : public Expr {
//public:

//private:

//};

//class Directive : public Expr {
//  public:
//    typedef std::vector<std::vector<std::string> > Parameter;
//    Directive();
//    Directive(const Parameter& params);
//    virtual ~Directive();

//    virtual void accept(Visitor& visitor, HttpConfig& svconf);

//    void    add(const Parameter& params);
//    void    addParam(const Parameter& param);

//    const Parameter&          getParams() const;
//    std::vector<std::string>  getValueByKey(const std::string& key);

//  private:
//    Parameter                   _params;
//    std::vector<std::string>    _keys;
//    Parameter                   _values;

//    void    addKeyValues(const std::vector<std::string>& item);
//};

#endif
