#include "Expr.hpp"

Context::Context() :_leftExpr(NULL), _rightExpr(NULL) {}

Context::Context(const Token& name)
    : _name(name)
    , _leftExpr(NULL)
    , _rightExpr(NULL)
{
}

Context::Context(const Token& name, const std::vector<std::string>& params,
                Expr* left, Expr* right)
    : _name(name)
    , _params(params)
    , _leftExpr(left)
    , _rightExpr(right)
{
}

Context::Context(const Context& c)
    : _name(c._name)
    , _params(c._params)
    , _leftExpr(NULL)
    , _rightExpr(NULL)
{
    if (c._leftExpr) {
        _leftExpr = new Context();
        *_leftExpr = *c._leftExpr;
    }
    if (c._rightExpr) {
        _rightExpr = new Context();
        *_rightExpr = *c._rightExpr;
    }
}

Context::~Context() {
    delete _leftExpr;
    _leftExpr = NULL;
    delete _rightExpr;
    _rightExpr = NULL;
}

void    Context::accept(Visitor& visitor) {
    visitor.visitContextExpr(*this);
}

Token&  Context::getName() { return _name; }

std::vector<std::string>&   Context::getParams() {
    return _params;
}

Expr*   Context::getLeftExpr() { return _leftExpr; }

Expr*   Context::getRightExpr() { return _rightExpr; }

void    Context::addParam(const std::string& param) {
    _params.push_back(param);
}

void    Context::addExprToLeft(Expr* left) {
    _leftExpr = left;
}

void    Context::addExprToRight(Expr* right) {
    _rightExpr = right;
}
