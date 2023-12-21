#include "AstPrinter.hpp"
#include "ConfigInfo.hpp"

AstPrinter::~AstPrinter() {}

void    AstPrinter::print(Expr& expr, ConfigInfo& conf) {
    expr.accept(*this, conf);
}

void    AstPrinter::visitMainContextExpr(MainContext& expr,
                                    __attribute__((unused)) ConfigInfo& conf) {
    parenthesize(conf, "group", 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    AstPrinter::visitServerContextExpr(ServerContext& expr,
                                    __attribute__((unused)) ConfigInfo& conf) {
    parenthesize(conf, "server", 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    AstPrinter::visitLocationContextExpr(LocationContext& expr,
                                    __attribute__((unused)) ConfigInfo& conf) {
    parenthesize(conf, "location", 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    AstPrinter::visitDirectiveExpr(Directive& expr,
                                    __attribute__((unused)) ConfigInfo& conf) {
    parenthesize(conf, expr.getOperator().getLexeme(), 1, expr.getRightExpr());
}

void    AstPrinter::visitParameterExpr(Parameter& expr,
                                    __attribute__((unused)) ConfigInfo& conf) {
    std::cout << "[";
    for (size_t i = 0; i < expr.getParams().size(); ++i)
        std::cout << " " << expr.getParams()[i];
    std::cout << " ] ";
}

void    AstPrinter::parenthesize(ConfigInfo& conf, const std::string& name,
                                int n, ...)
{
    va_list ap;
    Expr*   expr;

    va_start(ap, n);
    std::cout << "(" << name;
    for (int i = 0; i < n; ++i) {
        expr = va_arg(ap, Expr*);
        if (expr == NULL)
            continue;
        expr->accept(*this, conf);
    }
    va_end(ap);
    std::cout << ")";
}
