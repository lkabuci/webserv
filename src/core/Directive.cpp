#include "Expr.hpp"

Directive::Directive() : _params() {}

Directive::Directive(const Parameter& params) : _params(params) {}

Directive::~Directive() {}

void    Directive::accept(Visitor& visitor) {
    visitor.visitDirectiveExpr(*this);
}

const Directive::Parameter& Directive::getParams() { return _params; }

void    Directive::add(std::vector<Parameter>& params) {
    std::vector<Parameter>::iterator    it = params.begin();

    for (; it != params.end(); ++it)
        _params.insert(it->begin(), it->end());
}
