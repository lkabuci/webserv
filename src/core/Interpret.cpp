#include "Interpret.hpp"

Interpret::~Interpret() {}

void    Interpret::interpret(std::list<std::shared_ptr<Expr> > exprs) {
    for (auto expr : exprs)
        evaluate(*expr);
}

void    Interpret::evaluate(Expr& expr) {
    expr.accept(*this);
}

void    Interpret::visitStringExpr(String& expr) {
    std::cout << expr.getValue();
}

void    Interpret::visitNumberExpr(Number& expr) {
    std::cout << expr.getValue();
}

void    Interpret::visitGroupingExpr(Grouping& expr) {
    evaluate(expr);
}

void    Interpret::visitBinaryExpr(Binary& expr) {
    evaluate(expr.getLeftExpr());
    evaluate(expr.getRightExpr());
}
