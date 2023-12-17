#pragma once

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "Token.hpp"
#include "Visitor.hpp"
#include "common.hpp"

class Expr {
public:
  virtual ~Expr() {}

  virtual void  accept(Visitor& visitor) = 0;
};

class MainContext : public Expr {
  public:
    MainContext();
    MainContext(Expr* left, Expr* right);
    MainContext(const MainContext& mc);
    virtual ~MainContext();

    MainContext&  operator=(const MainContext& mc);

    virtual void accept(Visitor& visitor);

    Expr* getLeftExpr();
    Expr* getRightExpr();

  private:
    Expr* _leftExpr;
    Expr* _rightExpr;

    void  swap(MainContext mc);
};

class Context : public Expr {
  public:
    Context();
    Context(const Token& name);
    Context(const Token& name, const std::vector<std::string>& params,
            Expr* left, Expr* right);
    Context(const Context& c);
    virtual ~Context();

    Context&  operator=(const Context& c);

    virtual void accept(Visitor& visitor);

    Token& getName();
    std::vector<std::string>& getParams();
    Expr* getLeftExpr();
    Expr* getRightExpr();

    void addParam(const std::string& param);
    void addExprToLeft(Expr* left);
    void addExprToRight(Expr* right);

  private:
    Token                     _name;
    std::vector<std::string>  _params;
    Expr*                     _leftExpr;
    Expr*                     _rightExpr;
};

class Directive : public Expr {
  public:
    typedef std::map<std::string, std::vector<std::string> > Parameter;
    Directive();
    Directive(const Parameter& params);
    virtual ~Directive();

    virtual void accept(Visitor& visitor);

    const Parameter& getParams();

    void add(std::vector<Parameter>& params);

  private:
    Parameter _params;
};

#endif
