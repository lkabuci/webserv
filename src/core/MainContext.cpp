#include "Expr.hpp"

MainContext::MainContext() : _leftExpr(NULL), _rightExpr(NULL) {}

MainContext::MainContext(Expr* left, Expr* right)
    : _leftExpr(left)
    , _rightExpr(right)
{
}

MainContext::MainContext(const MainContext& mc)
    : _leftExpr(NULL)
    , _rightExpr(NULL)
{
    if (mc._leftExpr) {
        _leftExpr = new MainContext();
        *_leftExpr = *mc._leftExpr;
    }
    if (mc._rightExpr) {
        _rightExpr = new MainContext();
        *_rightExpr = *mc._rightExpr;
    }
}

MainContext&    MainContext::operator=(const MainContext& mc) {
    swap(mc);
    return *this;
}

MainContext::~MainContext() {
    delete _leftExpr;
    _leftExpr = NULL;
    delete _rightExpr;
    _rightExpr = NULL;
}

void    MainContext::swap(MainContext mc) {
    Expr*   tempLeft = mc._leftExpr;
    Expr*   tempRight = mc._rightExpr;

    mc._leftExpr = _leftExpr;
    mc._rightExpr = _rightExpr;
    _leftExpr = tempLeft;
    _rightExpr = tempRight;
}

void    MainContext::accept(Visitor& visitor) {
    visitor.visitMainContextExpr(*this);
}

Expr*   MainContext::getLeftExpr() { return _leftExpr; }

Expr*   MainContext::getRightExpr() { return _rightExpr; }
