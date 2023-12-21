#include "SetConfiguration.hpp"
#include "ConfigInfo.hpp"
#include "Expr.hpp"
#include "ServerConfig.hpp"
#include "TokenType.hpp"
#include "Visitor.hpp"
#include <cstdarg>

SetConfiguration::~SetConfiguration() {}

void    SetConfiguration::accept(Expr& expr, ConfigInfo& conf) {
    expr.accept(*this, conf);
}

void    SetConfiguration::visitMainContextExpr(MainContext& expr,
                                            ConfigInfo& conf)
{
    visit(conf, 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    SetConfiguration::visitServerContextExpr(ServerContext& expr,
                                            ConfigInfo& conf)
{
    visit(conf, 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    SetConfiguration::visitLocationContextExpr(LocationContext& expr,
                                            ConfigInfo& conf)
{
    visit(conf, 2, expr.getLeftExpr(), expr.getRightExpr());
}

void    SetConfiguration::visitDirectiveExpr(Directive& expr, ConfigInfo& conf)
{
    //switch (expr.getOperator().getType()) {
    //    case SERVER_NAME:
    //        conf.setHost(getHostName(expr.getRightExpr()));
    //        break;
    //    case LISTEN:
    //        conf.setPort(getPortNumber(expr.getRightExpr()));
    //        break;
    //    case ROOT:
    //        conf.setRoot(getRoot(expr.getRightExpr()));
    //        break;
    //}
    visit(conf, 1, expr.getRightExpr());
}

void    SetConfiguration::visitParameterExpr(Parameter& expr, ConfigInfo& conf)
{

}

void    SetConfiguration::visit(ConfigInfo& conf, int n, ...) {
    Expr*   expr;
    va_list ap;

    va_start(ap, n);
    for (int i = 0; i < n; ++i ) {
        expr = va_arg(ap, Expr*);
        if (!expr)
            continue;
        expr->accept(*this, conf);
    }
    va_end(ap);
}

