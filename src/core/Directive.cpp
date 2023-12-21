#include "ConfigInfo.hpp"
#include "Expr.hpp"

Directive::Directive() : _right(NULL) {}

Directive::Directive(const Token& opt, Expr* right) : _opt(opt), _right(right) {
}

Directive::Directive(const Directive& directive)
    : _opt(directive._opt)
    , _right(NULL)
{
    if (directive._right) {
        _right = new Directive();
        *_right = *directive._right;
    }
}

Directive::~Directive() {
    delete _right;
    _right = NULL;
}

Directive&  Directive::operator=(const Directive& directive) {
    _opt = directive._opt;
    _swap(directive);
    return *this;
}

void    Directive::_swap(Directive directive) {
    Expr*   right = directive._right;

    directive._right = _right;
    _right = right;
}

const Token&    Directive::getOperator() const { return _opt; }

Expr*   Directive::getRightExpr() { return _right; }

void    Directive::accept(Visitor& visitor, ConfigInfo& conf) {
    visitor.visitDirectiveExpr(*this, conf);
}
