#include "ConfigInfo.hpp"
#include "Expr.hpp"

Parameter::Parameter() {}

Parameter::Parameter(const std::vector<std::string>& params) : _params(params) {
}

Parameter::Parameter(const Parameter& param) : _params(param._params) {}

Parameter::~Parameter() {}

Parameter&  Parameter::operator=(const Parameter& param) {
    _params = param._params;
    return *this;
}

const std::vector<std::string>& Parameter::getParams() const { return _params; }

void    Parameter::accept(Visitor& visitor, ConfigInfo& conf) {
    visitor.visitParameterExpr(*this, conf);
}
