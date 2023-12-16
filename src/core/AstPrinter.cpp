#include "AstPrinter.hpp"

AstPrinter::~AstPrinter() {}

void    AstPrinter::print(Expr& stmt) {
    stmt.accept(*this);
}

void    AstPrinter::visitMainContextExpr(MainContext& stmt) {
    parenthesize("block", {&stmt.getLeftExpr(), &stmt.getRightExpr()});
}

void    AstPrinter::visitContextExpr(Context& stmt) {
    std::cout << stmt.getName().getLexeme();
    if (!stmt.getParams().empty()) {
        std::cout << " [";
        for (auto param : stmt.getParams())
            std::cout << " " << param;
        std::cout << " ]";
    }
    std::cout << " (";
    parenthesize("", {&stmt.getLeftExpr(), &stmt.getRightExpr()});
    std::cout << ") ";
}

void    AstPrinter::visitDirectiveExpr(Directive& stmt) {
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
                                std::initializer_list<Expr*> stmts)
{
    std::cout << "{ " << name;
    for (auto stmt : stmts) {
        if (!stmt)
            continue;
        std::cout << " ";
        stmt->accept(*this);
    }
    std::cout << "}";
}
