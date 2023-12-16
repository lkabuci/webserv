#include "Expr.hpp"

Context::Context(const std::shared_ptr<Token>& name) : _name(name) {}

Context::Context(const std::shared_ptr<Token>& name,
                const std::vector<std::string>& params,
                const std::shared_ptr<Expr>& left,
                const std::shared_ptr<Expr>& right)
    : _name(name)
    , _params(params)
    , _leftExpr(left)
    , _rightExpr(right)
{
}

void    Context::accept(Visitor& visitor) {
    visitor.visitContextExpr(*this);
}

Token&  Context::getName() { return *_name; }

std::vector<std::string>&   Context::getParams() {
    return _params;
}

Expr&   Context::getLeftExpr() { return *_leftExpr; }

Expr&   Context::getRightExpr() { return *_rightExpr; }

void    Context::addParam(const std::string& param) {
    _params.push_back(param);
}

void    Context::addExprToLeft(const std::shared_ptr<Expr>& left) {
    _leftExpr = left;
}

void    Context::addExprToRight(const std::shared_ptr<Expr>& right) {
    _rightExpr = right;
}
