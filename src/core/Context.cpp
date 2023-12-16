#include "Stmt.hpp"

Context::Context(const std::shared_ptr<Token>& name) : _name(name) {}

Context::Context(const std::shared_ptr<Token>& name,
                const std::vector<std::string>& params,
                const std::shared_ptr<Stmt>& left,
                const std::shared_ptr<Stmt>& right)
    : _name(name)
    , _params(params)
    , _leftStmt(left)
    , _rightStmt(right)
{
}

void    Context::accept(Visitor& visitor) {
    visitor.visitContextStmt(*this);
}

Token&  Context::getName() { return *_name; }

std::vector<std::string>&   Context::getParams() {
    return _params;
}

Stmt&   Context::getLeftExpr() { return *_leftStmt; }

Stmt&   Context::getRightStmt() { return *_rightStmt; }

void    Context::addParam(const std::string& param) {
    _params.push_back(param);
}

void    Context::addStmtToLeft(const std::shared_ptr<Stmt>& left) {
    _leftStmt = left;
}

void    Context::addStmtToRight(const std::shared_ptr<Stmt>& right) {
    _rightStmt = right;
}
