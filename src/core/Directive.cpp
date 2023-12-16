#include "Stmt.hpp"

Directive::Directive() : _params() {}

Directive::Directive(const Parameter& params) : _params(params) {}

void    Directive::accept(Visitor& visitor) {
    visitor.visitDirectiveStmt(*this);
}

const Directive::Parameter& Directive::getParams() { return _params; }

void    Directive::add(std::vector<Parameter>& params) {
    std::vector<Parameter>::iterator    it = params.begin();

    for (; it != params.end(); ++it)
        _params.insert(it->begin(), it->end());
}
