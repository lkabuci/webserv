#include "AstPrinter.hpp"

AstPrinter::~AstPrinter() {}

void    AstPrinter::print(Expr& expr) {
    expr.accept(*this);
}

void    AstPrinter::visitMainContextExpr(MainContext& expr) {
    parenthesize("group", 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    AstPrinter::visitServerContextExpr(ServerContext& expr) {
    parenthesize("server", 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    AstPrinter::visitLocationContextExpr(LocationContext& expr) {
    parenthesize("location", 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    AstPrinter::visitDirectiveExpr(Directive& expr) {
    parenthesize(expr.getOperator().getLexeme(), 1, expr.getRightExpr());
}

void    AstPrinter::visitParameterExpr(Parameter& expr) {
    std::cout << "[";
    for (size_t i = 0; i < expr.getParams().size(); ++i)
        std::cout << " " << expr.getParams()[i];
    std::cout << " ] ";
}

void    AstPrinter::parenthesize(const std::string& name, int n, ...) {
    va_list ap;
    Expr*   expr;

    va_start(ap, n);
    std::cout << "(" << name;
    for (int i = 0; i < n; ++i) {
        expr = va_arg(ap, Expr*);
        if (expr == NULL)
            continue;
        expr->accept(*this);
    }
    va_end(ap);
    std::cout << ")";
}
