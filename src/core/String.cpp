#include "Expr.hpp"

String::String(const std::string& value) : _value(value) {}

String::~String() {}

void    String::accept(Visitor& visitor) {
    return visitor.visitStringExpr(*this);
}

const std::string&  String::getValue() const { return _value; }
