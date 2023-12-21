#include "ConfigInfo.hpp"
#include "Expr.hpp"

MainContext::MainContext() : _left(NULL), _right(NULL) {}

MainContext::MainContext(Expr* left, Expr* right) : _left(left), _right(right) {
}

MainContext::MainContext(const MainContext& mainContext)
    : _left(NULL)
    , _right(NULL)
{
    if (mainContext._left) {
        _left = new MainContext();
        *_left = *mainContext._left;
    }
    if (mainContext._right) {
        _right = new MainContext();
        *_right = *mainContext._right;
    }
}

MainContext::~MainContext() {
    delete _left;
    delete _right;
}

MainContext&    MainContext::operator=(const MainContext& mainContext) {
    _swap(mainContext);
    return *this;
}

void    MainContext::accept(Visitor& visitor, ConfigInfo& conf) {
    visitor.visitMainContextExpr(*this, conf);
}

Expr*   MainContext::getLeftExpr() { return _left; }

Expr*   MainContext::getRightExpr() { return _right; }

void    MainContext::_swap(MainContext mainContext) {
    Expr*   left = mainContext._left;
    Expr*   right = mainContext._right;

    mainContext._left = _left;
    mainContext._right = _right;
    _left = left;
    _right = right;
}
