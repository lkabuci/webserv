#include "Expr.hpp"

Grouping::Grouping(std::shared_ptr<Expr> expr) : _expr(expr) {}

Grouping::~Grouping() {}

void    Grouping::accept(Visitor& visitor) {
    return visitor.visitGroupingExpr(*this);
}

Expr&   Grouping::getExpr() { return *_expr; }
