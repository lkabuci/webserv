#include "Expr.hpp"

Number::Number(size_t value) : _value(value) {}

Number::~Number() {}

void    Number::accept(Visitor& visitor) {
    return visitor.visitNumberExpr(*this);
}

size_t  Number::getValue() const { return _value; }
