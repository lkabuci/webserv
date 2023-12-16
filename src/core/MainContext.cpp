#include "Stmt.hpp"

MainContext::MainContext(const std::shared_ptr<Stmt>& left,
                        const std::shared_ptr<Stmt>& right)
    : _leftStmt(left)
    , _rightStmt(right)
{
}

void    MainContext::accept(Visitor& visitor) {
    visitor.visitMainContextStmt(*this);
}

MainContext::~MainContext() {}

Stmt&   MainContext::getLeftStmt() { return *_leftStmt; }

Stmt&   MainContext::getRightStmt() { return *_rightStmt; }
