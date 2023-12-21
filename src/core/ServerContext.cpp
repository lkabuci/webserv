#include "Expr.hpp"

ServerContext::ServerContext() : _left(NULL), _right(NULL) {}

ServerContext::ServerContext(Expr* left, Expr* right)
    : _left(left)
    , _right(right)
{
}

ServerContext::ServerContext(const ServerContext& context)
    : _left(NULL)
    , _right(NULL)
{
    if (context._left) {
        _left = new ServerContext();
        *_left = *context._left;
    }
    if (context._right) {
        _right = new ServerContext();
        *_right = *context._right;
    }
}

ServerContext::~ServerContext() {
    delete _left;
    _left = NULL;
    delete _right;
    _right = NULL;
}

ServerContext&    ServerContext::operator=(const ServerContext& context) {
    _swap(context);
    return *this;
}

void    ServerContext::_swap(ServerContext context) {
    Expr*   left = context._left;
    Expr*   right = context._right;

    context._left = _left;
    context._right = _right;
    _left = left;
    _right = right;
}

Expr*   ServerContext::getRightExpr() { return _right; }

Expr*   ServerContext::getLeftExpr() { return _left; }

void    ServerContext::accept(Visitor& visitor) {
    visitor.visitServerContextExpr(*this);
}
