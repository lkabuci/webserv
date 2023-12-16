#include "AstPrinter.hpp"

AstPrinter::~AstPrinter() {}

//void    AstPrinter::print(Expr& expr) {
//    expr.accept(*this);
//}

//void    AstPrinter::visitBinaryExpr(Binary& expr) {
//    parenthesize(expr.getOperator().getLexeme(), {&expr.getLeftExpr(),
//                &expr.getRightExpr()});
//}

//void    AstPrinter::visitGroupingExpr(Grouping& expr) {
//    parenthesize("group", {&expr.getExpr()});
//}

//void    AstPrinter::visitStringExpr(String& expr) {
//    parenthesize(expr.getValue(), {});
//}

//void    AstPrinter::visitNumberExpr(Number& expr) {
//    parenthesize(expr.getValue(), {});
//}

//template<typename T>
//void    AstPrinter::parenthesize(const T &value,
//                                std::initializer_list<Expr *> exprs)
//{
//    std::cout << "{" << value;
//    for (auto expr : exprs) {
//        std::cout << " ";
//        expr->accept(*this);
//    }
//    std::cout << "}";
//}

void    AstPrinter::print(Stmt& stmt) {
    stmt.accept(*this);
}

void    AstPrinter::visitMainContextStmt(MainContext& stmt) {
    parenthesize("block", {&stmt.getLeftStmt(), &stmt.getRightStmt()});
}

void    AstPrinter::visitContextStmt(Context& stmt) {
    std::cout << "$-";
    std::cout << stmt.getName().getLexeme();
    if (!stmt.getParams().empty()) {
        std::cout << " [";
        for (auto param : stmt.getParams())
            std::cout << " " << param;
        std::cout << " ]";
    }
    std::cout << " (";
    parenthesize("inter_block", {&stmt.getLeftExpr(), &stmt.getRightStmt()});
    std::cout << ") ";
}

void    AstPrinter::visitDirectiveStmt(Directive& stmt) {
    if (stmt.getParams().empty())
        return;
    std::cout << "[";
    for (auto param : stmt.getParams()) {
        std::cout << " -" << param.first << ":";
        for (auto value : param.second)
            std::cout << " " << value;
    }
    std::cout << "]";
}

void    AstPrinter::parenthesize(const std::string& name,
                                std::initializer_list<Stmt*> stmts)
{
    std::cout << "{ " << name;
    for (auto stmt : stmts) {
        if (!stmt)
            continue;
        std::cout << " ";
        stmt->accept(*this);
    }
    std::cout << "} ";
}
