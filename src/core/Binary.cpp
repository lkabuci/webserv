#include "Expr.hpp"

Binary::Binary(std::shared_ptr<Expr> left, std::shared_ptr<Token> opt,
                std::shared_ptr<Expr> right)
    : _left(left)
    , _opt(opt)
    , _right(right)
{
}

Binary::~Binary() {}

void    Binary::accept(Visitor& visitor) {
    visitor.visitBinaryExpr(*this);
}

Expr&   Binary::getLeftExpr() { return *_left; }

Token   Binary::getOperator() { return *_opt; }

Expr&   Binary::getRightExpr() { return *_right; }
