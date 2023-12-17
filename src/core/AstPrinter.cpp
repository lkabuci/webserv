#include "AstPrinter.hpp"

AstPrinter::~AstPrinter() {}

void    AstPrinter::print(Expr& stmt) {
    stmt.accept(*this);
}

void    AstPrinter::visitMainContextExpr(MainContext& stmt) {
    parenthesize("block", 2, stmt.getLeftExpr(), stmt.getRightExpr());
}

void    AstPrinter::visitContextExpr(Context& stmt) {
    std::cout << stmt.getName().getLexeme();
    if (!stmt.getParams().empty()) {
        std::vector<std::string>::iterator  it = stmt.getParams().begin();
        std::cout << " [";
        for (; it != stmt.getParams().end(); ++it)
            std::cout << " " << *it;
        std::cout << " ]";
    }
    std::cout << " (";
    parenthesize("", 2, stmt.getLeftExpr(), stmt.getRightExpr());
    std::cout << ") ";
}

void    AstPrinter::visitDirectiveExpr(Directive& stmt) {
    if (stmt.getParams().empty())
        return;
    Directive::Parameter                pramas = stmt.getParams();
    Directive::Parameter::iterator      it = pramas.begin();
    std::vector<std::string>::iterator  itvec;
    std::cout << "[";
    for (; it != pramas.end(); ++it) {
        std::cout << " -" << it->first << ":";
        for (itvec = it->second.begin(); itvec != it->second.end(); ++itvec)
            std::cout << " " << *itvec;
    }
    std::cout << "]";
}

void    AstPrinter::parenthesize(const std::string& name, int n, ...)
{
    va_list ap;
    va_start(ap, n);

    std::cout << "{ " << name;
    for (int i = 0; i < n; ++i) {
        Expr*   ptr = va_arg(ap, Expr*);
        if (!ptr)
            continue;
        std::cout << " ";
        ptr->accept(*this);
    }
    std::cout << "}";
}
