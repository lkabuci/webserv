#include "AstPrinter.hpp"

AstPrinter::~AstPrinter() {}

void    AstPrinter::print(Stmt& stmt) {
    stmt.accept(*this);
}

void    AstPrinter::visitMainContextStmt(MainContext& stmt) {
    parenthesize("block", {&stmt.getLeftStmt(), &stmt.getRightStmt()});
}

void    AstPrinter::visitContextStmt(Context& stmt) {
    std::cout << stmt.getName().getLexeme();
    if (!stmt.getParams().empty()) {
        std::cout << " [";
        for (auto param : stmt.getParams())
            std::cout << " " << param;
        std::cout << " ]";
    }
    std::cout << " (";
    parenthesize("", {&stmt.getLeftExpr(), &stmt.getRightStmt()});
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
    std::cout << "}";
}
