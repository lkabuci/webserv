#include "Parameter.hpp"

Parameter::Parameter() {}

Parameter::Parameter(const std::string& attribute, const std::string& value)
    : _attribute(attribute), _value(value) {}

Parameter::Parameter(const Parameter& parameter)
    : _attribute(parameter._attribute), _value(parameter._value) {}

Parameter& Parameter::operator=(const Parameter& parameter) {
    if (this == &parameter)
        return *this;
    _attribute = parameter._attribute;
    _value = parameter._value;
    return *this;
}

const std::string& Parameter::attribute() const {
    return _attribute;
}

const std::string& Parameter::value() const {
    return _value;
}

void Parameter::set_attribute(const std::string& attribute) {
    _attribute = attribute;
}

void Parameter::set_value(const std::string& value) {
    _value = value;
}
