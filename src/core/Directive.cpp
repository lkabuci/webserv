#include "Expr.hpp"

Directive::Directive() : _right(NULL) {}

Directive::Directive(const Token& opt, Expr* right) : _opt(opt), _right(right) {
}

Directive::Directive(const Directive& directive)
    : _opt(directive._opt)
    , _right(NULL)
{
    if (directive._right) {
        _right = new Directive();
        *_right = *directive._right;
    }
}

Directive::~Directive() {
    delete _right;
    _right = NULL;
}

Directive&  Directive::operator=(const Directive& directive) {
    _opt = directive._opt;
    _swap(directive);
    return *this;
}

void    Directive::_swap(Directive directive) {
    Expr*   right = directive._right;

    directive._right = _right;
    _right = right;
}

const Token&    Directive::getOperator() const { return _opt; }

Expr*   Directive::getRightExpr() { return _right; }

void    Directive::accept(Visitor& visitor) {
    visitor.visitDirectiveExpr(*this);
}

//Directive::Directive() : _params() {}

//Directive::Directive(const Parameter& params) : _params(params) {
//}

//Directive::~Directive() {}

//void    Directive::accept(Visitor& visitor, HttpConfig& conf) {
//    visitor.visitDirectiveExpr(*this, conf);
//}

//void    Directive::add(const Parameter& params) {
//    _params.insert(_params.end(), params.begin(), params.end());
//    Parameter::const_iterator   it = params.begin();

//    for (; it != params.end(); ++it)
//        addKeyValues(*it);
//}

//void    Directive::addKeyValues(const std::vector<std::string>& item) {
//    std::vector<std::string>    values;

//    _keys.push_back(item[0]);
//    values.insert(values.begin(), item.begin() + 1, item.end());
//    _values.push_back(values);
//}

//const Directive::Parameter& Directive::getParams() const { return _params; }

//std::vector<std::string> Directive::getValueByKey(const std::string& key)
//{
//    std::vector<std::string>    result;
//    size_t i = 0;

//    for (; i < _keys.size(); ++i) {
//        if (_keys[i] == key) {
//            result = _values[i];
//            _keys.erase(_keys.begin() + i);
//            _values.erase(_values.begin() + i);
//            break;
//        }
//    }
//    return result;
//}
