//#pragma once

//#ifndef __INTERPRET_HPP__
//#define __INTERPRET_HPP__

//#include "HttpConfig.hpp"

//class   Interpret : public Visitor {
//public:
//    virtual ~Interpret();

//    void    evalute(Expr* expr, HttpConfig& svconf);

//    virtual void    visitMainContextExpr(MainContext& expr, HttpConfig& conf);
//    virtual void    visitContextExpr(Context& expr, HttpConfig& conf);
//    virtual void    visitLocationContextExpr(Context& expr, HttpConfig& conf);
//    virtual void    visitDirectiveExpr(Directive& expr, HttpConfig& conf);

//private:
//    int _getport(const std::vector<std::string>& value);

//    HttpConfig::keyVector   _getErrorPages(Directive& expr);
//    void                    _addcodes(const std::vector<std::string>& temp,
//                                    std::vector<size_t>& codes);

//};

//#endif
