#include "Headers.hpp"

Headers::Headers() {}

Headers::Headers(const std::string& type, const std::string& subtype)
    : _type(type), _subtype(subtype) {}

Headers::Headers(const Headers& header)
    : _parser(header._parser), _type(header._type), _subtype(header._subtype) {}

Headers& Headers::operator=(const Headers& header) {
    if (this == &header)
        return *this;
    _parser = header._parser;
    _type = header._type;
    _subtype = header._subtype;
    return *this;
}

const std::string& Headers::type() const {
    return _type;
}

const std::string& Headers::subtype() const {
    return _subtype;
}

void Headers::set_type(const std::string& type) {
    _type = type;
}

void Headers::set_subtype(const std::string& subtype) {
    _subtype = subtype;
}
