#pragma once

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "Token.hpp"
#include "Visitor.hpp"
#include "common.hpp"

class MainContext;
class Context;
class Directive;

class Expr {
  public:
    virtual ~Expr() {}

    virtual void accept(Visitor& visitor) = 0;
};

class MainContext : public Expr {
  public:
    MainContext() = default;
    MainContext(const std::shared_ptr<Expr>& left,
                const std::shared_ptr<Expr>& right);
    virtual ~MainContext();

    virtual void accept(Visitor& visitor) override;

    Expr& getLeftExpr();
    Expr& getRightExpr();

  private:
    std::shared_ptr<Expr> _leftExpr;
    std::shared_ptr<Expr> _rightExpr;
};

class Context : public Expr {
  public:
    Context() = default;
    Context(const std::shared_ptr<Token>& name);
    Context(const std::shared_ptr<Token>& name,
            const std::vector<std::string>& params,
            const std::shared_ptr<Expr>& left,
            const std::shared_ptr<Expr>& right);
    virtual ~Context() {}

    virtual void accept(Visitor& visitor) override;

    Token& getName();
    std::vector<std::string>& getParams();
    Expr& getLeftExpr();
    Expr& getRightExpr();

    void addParam(const std::string& param);
    void addExprToLeft(const std::shared_ptr<Expr>& left);
    void addExprToRight(const std::shared_ptr<Expr>& right);

  private:
    std::shared_ptr<Token> _name;
    std::vector<std::string> _params;
    std::shared_ptr<Expr> _leftExpr;
    std::shared_ptr<Expr> _rightExpr;
};

class Directive : public Expr {
  public:
    typedef std::map<std::string, std::vector<std::string>> Parameter;
    Directive();
    Directive(const Parameter& params);
    virtual ~Directive() {}

    virtual void accept(Visitor& visitor);

    const Parameter& getParams();

    void add(std::vector<Parameter>& params);

  private:
    Parameter _params;
};

#endif
