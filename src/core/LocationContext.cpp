#include "ConfigInfo.hpp"
#include "Expr.hpp"

LocationContext::LocationContext() : _left(NULL), _right(NULL) {}

LocationContext::LocationContext(Expr* left, Expr* right)
    : _left(left)
    , _right(right)
{
}

LocationContext::LocationContext(const LocationContext& context)
    : _left(NULL)
    , _right(NULL)
{
    if (context._left) {
        _left = new LocationContext();
        *_left = *context._left;
    }
    if (context._right) {
        _right = new LocationContext();
        *_right = *context._right;
    }
}

LocationContext::~LocationContext() {
    delete _left;
    _left = NULL;
    delete _right;
    _right = NULL;
}

LocationContext&    LocationContext::operator=(const LocationContext& context) {
    _swap(context);
    return *this;
}

void    LocationContext::_swap(LocationContext context) {
    Expr*   left = context._left;
    Expr*   right = context._right;

    context._left = _left;
    context._right = _right;
    _left = left;
    _right = right;
}

Expr*   LocationContext::getRightExpr() { return _right; }

Expr*   LocationContext::getLeftExpr() { return _left; }

void    LocationContext::accept(Visitor& visitor, ConfigInfo& conf) {
    visitor.visitLocationContextExpr(*this, conf);
}
