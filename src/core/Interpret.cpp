//#include "Interpret.hpp"

//Interpret::~Interpret() {}

//void    Interpret::evalute(Expr* expr, HttpConfig& conf) {
//    if (expr == NULL)
//        return;
//    expr->accept(*this, conf);
//}

//void    Interpret::visitMainContextExpr(MainContext& expr, HttpConfig& conf) {
//    if (expr.getLeftExpr())
//        expr.getLeftExpr()->accept(*this, conf);
//    if (expr.getRightExpr())
//        expr.getRightExpr()->accept(*this, conf);
//}

//void    Interpret::visitContextExpr(Context& expr, HttpConfig& conf) {
//    if (expr.getName().getType() == LOCATION_CONTEXT) {
//        static_cast<ServerConfig&>(conf).addLocation(
//                                        LocationConfig(expr.getParams()[0]));
//        std::cout << static_cast<ServerConfig&>(conf).getLocations().size() << '\n';
//    }
//    evalute(expr.getLeftExpr(), conf);
//    evalute(expr.getRightExpr(), conf);
//}

//void    Interpret::visitLocationContextExpr(Context& expr, HttpConfig& conf) {
//    //std::cout << "Entered\n";
//    ServerConfig&   temp = static_cast<ServerConfig&>(conf);

//    //throw std::runtime_error("ERROR");
//    for (size_t i = 0; i < temp.getLocations().size(); ++i) {
//        std::cout << "--------\n";
//        evalute(expr.getLeftExpr(), temp.getLocations()[i]);
//    }
//}

//void    Interpret::visitDirectiveExpr(Directive& expr, HttpConfig& conf) {
//    size_t  port = _getport(expr.getValueByKey("listen"));
//    std::vector<std::string>    domainName = expr.getValueByKey("server_name");

//    //if (domainName.empty())
//    //    throw std::runtime_error("server_name is a mandatory directive.");
//    std::vector<std::string>    rootVec = expr.getValueByKey("root");

//    std::string rootDir;
//    if (!rootVec.empty()) {
//        //if (rootVec.size() != 1)
//        //    throw std::runtime_error("Invalid root directory.");
//        rootDir = rootVec[0];
//    }
//    std::vector<std::string>    indexFiles = expr.getValueByKey("index");
//    HttpConfig::keyVector   errorPages;

//    errorPages = _getErrorPages(expr);

//    conf.setPort(port);
//    conf.setDomainName(domainName);
//    conf.setRootDir(rootDir);
//    conf.setIndexFiles(indexFiles);
//    conf.setErrorPages(errorPages);
//}

//int Interpret::_getport(const std::vector<std::string>& value) {
//    if (value.empty())
//        return 0;
//    //    throw std::runtime_error("Invalid port number.");
//    std::stringstream   ss(value[0]);
//    int                 port;

//    if (!(ss >> port) || port < 0)
//        throw std::runtime_error("Invalid port number.");
//    return port;
//}

//HttpConfig::keyVector   Interpret::_getErrorPages(Directive& expr) {
//    HttpConfig::keyVector        result;
//    std::vector<size_t>         codes;
//    std::string                 path;
//    std::vector<std::string>    temp;

//    while (!(temp = expr.getValueByKey("error_page")).empty()) {
//        if (temp.size() < 2)
//            throw std::runtime_error("Invalid error page expression.");
//        path = temp[temp.size() - 1];
//        _addcodes(temp, codes);
//        result[path] = codes;
//        codes.clear();
//    }
//    return result;
//}

//void    Interpret::_addcodes(const std::vector<std::string>& temp,
//                            std::vector<size_t>& codes)
//{
//    std::stringstream   ss;
//    int                 val;

//    for (size_t i = 0; i < temp.size() - 1; ++i) {
//        ss << temp[i];
//        if (!(ss >> val) || val < 0)
//            throw std::runtime_error("Invalid error page code.");
//        codes.push_back(static_cast<size_t>(val));
//        ss.clear();
//    }
//}
