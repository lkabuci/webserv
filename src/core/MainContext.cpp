#include "Expr.hpp"

MainContext::MainContext(const std::shared_ptr<Expr>& left,
                        const std::shared_ptr<Expr>& right)
    : _leftExpr(left)
    , _rightExpr(right)
{
}

void    MainContext::accept(Visitor& visitor) {
    visitor.visitMainContextExpr(*this);
}

MainContext::~MainContext() {}

Expr&   MainContext::getLeftExpr() { return *_leftExpr; }

Expr&   MainContext::getRightExpr() { return *_rightExpr; }
