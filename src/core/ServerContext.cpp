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

//const Token&    ServerContext::getOperator() const { return _opt; }

void    ServerContext::accept(Visitor& visitor) {
    visitor.visitServerContextExpr(*this);
}

//Context::Context() :_leftExpr(NULL), _rightExpr(NULL) {}

//Context::Context(const Token& name)
//    : _name(name)
//    , _leftExpr(NULL)
//    , _rightExpr(NULL)
//{
//}

//Context::Context(const Token& name, const std::vector<std::string>& params,
//                Expr* left, Expr* right)
//    : _name(name)
//    , _params(params)
//    , _leftExpr(left)
//    , _rightExpr(right)
//{
//}

//Context::Context(const Context& c)
//    : _name(c._name)
//    , _params(c._params)
//    , _leftExpr(NULL)
//    , _rightExpr(NULL)
//{
//    if (c._leftExpr) {
//        _leftExpr = new Context();
//        *_leftExpr = *c._leftExpr;
//    }
//    if (c._rightExpr) {
//        _rightExpr = new Context();
//        *_rightExpr = *c._rightExpr;
//    }
//}

//Context::~Context() {
//    delete _leftExpr;
//    _leftExpr = NULL;
//    delete _rightExpr;
//    _rightExpr = NULL;
//}

//void    Context::accept(Visitor& visitor, HttpConfig& conf) {
//    if (_params.empty())
//        visitor.visitContextExpr(*this, conf);
//    else
//        visitor.visitLocationContextExpr(*this, conf);
//}

//Token&  Context::getName() { return _name; }

//std::vector<std::string>&   Context::getParams() {
//    return _params;
//}

//Expr*   Context::getLeftExpr() { return _leftExpr; }

//Expr*   Context::getRightExpr() { return _rightExpr; }

//void    Context::addParam(const std::string& param) {
//    _params.push_back(param);
//}

//void    Context::addExprToLeft(Expr* left) {
//    _leftExpr = left;
//}

//void    Context::addExprToRight(Expr* right) {
//    _rightExpr = right;
//}
