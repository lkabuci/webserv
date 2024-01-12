#include "ContentType.hpp"

ContentType::ContentType() {}

void ContentType::parse(const std::string& header) {
    _parser = Parse(header);

    if (!_parser.match(TOKEN))
        throw std::runtime_error("Invalid header name.");
    _type = _parser.previous().lexeme();
    _parser.consume(SLASH, "missing slash after type.");
    if (!_parser.match(TOKEN))
        throw std::runtime_error("Invalid header name.");
    _subtype = _parser.previous().lexeme();
    while (!_parser.is_at_end()) {
        while (_parser.check(SP) || _parser.check(HT))
            _parser.advance();
        _parser.consume(SEMICOLON, "missing semicolon.");
        while (_parser.check(SP) || _parser.check(HT))
            _parser.advance();
        parameter();
    }
}

void ContentType::parameter() {
    _parser.consume(TOKEN, "invalid parameter.");

    std::string attribute;
    std::string value;

    attribute = _parser.previous().lexeme();
    _parser.consume(EQUAL, "missing equal sign.");
    while (_parser.match(TOKEN) || _parser.match(QUOTED_STRING)) {
        value.append(_parser.previous().lexeme());
    }
    _parameters.push_back(Parameter(attribute, value));
}

const std::vector<Parameter>& ContentType::parameters() const {
    return _parameters;
}

void ContentType::add(const Parameter& parameter) {
    _parameters.push_back(parameter);
}

void ContentType::insert(const std::vector<Parameter>& items) {
    _parameters.insert(_parameters.end(), items.begin(), items.end());
}

const Parameter& ContentType::operator[](const size_t& i) const {
    return _parameters[i];
}
