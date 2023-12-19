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

//void    AstPrinter::print(Expr& stmt, HttpConfig& conf) {
//    stmt.accept(*this, conf);
//}

//void    AstPrinter::visitMainContextExpr(MainContext& stmt,
//                        __attribute__((unused))HttpConfig& conf)
//{
//    parenthesize(conf, "block", 2, stmt.getLeftExpr(), stmt.getRightExpr());
//}

//void    AstPrinter::visitContextExpr(Context& stmt,
//                        __attribute__((unused))HttpConfig& conf)
//{
//    std::cout << stmt.getName().getLexeme();
//    if (!stmt.getParams().empty()) {
//        std::vector<std::string>::iterator  it = stmt.getParams().begin();
//        std::cout << " [";
//        for (; it != stmt.getParams().end(); ++it)
//            std::cout << " " << *it;
//        std::cout << " ]";
//    }
//    std::cout << " (";
//    parenthesize(conf, "", 2, stmt.getLeftExpr(), stmt.getRightExpr());
//    std::cout << ") ";
//}

//void    AstPrinter::visitDirectiveExpr(Directive& stmt,
//                        __attribute__((unused))HttpConfig& conf)
//{
//    if (stmt.getParams().empty())
//        return;
//    Directive::Parameter                pramas = stmt.getParams();
//    Directive::Parameter::iterator      it = pramas.begin();
//    std::vector<std::string>::iterator  itvec;
//    std::cout << "[";
//    for (; it != pramas.end(); ++it) {
//        for (itvec = it->begin(); itvec != it->end(); ++itvec)
//            std::cout << " " << *itvec;
//    }
//    std::cout << "]";
//}

//void    AstPrinter::parenthesize(HttpConfig& conf, const std::string& name,
//                                int n, ...)
//{
//    va_list ap;
//    va_start(ap, n);

//    std::cout << "{ " << name;
//    for (int i = 0; i < n; ++i) {
//        Expr*   ptr = va_arg(ap, Expr*);
//        if (!ptr)
//            continue;
//        std::cout << " ";
//        ptr->accept(*this, conf);
//    }
//    std::cout << "}";
//}
