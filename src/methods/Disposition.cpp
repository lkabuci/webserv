#include "Disposition.hpp"

Disposition::Disposition() {}

Disposition::Disposition(const std::string& source) : _parser(source) {}

Disposition::Disposition(const std::string&            type,
                         const std::vector<Parameter>& param)
    : _type(type), _parameters(param) {}

Disposition::Disposition(const Disposition& desposition)
    : _parser(desposition._parser), _type(desposition._type),
      _parameters(desposition._parameters) {}

Disposition::~Disposition() {}

Disposition& Disposition::operator=(const Disposition& desposition) {
    if (this == &desposition)
        return *this;
    _parser = desposition._parser;
    _type = desposition._type;
    _parameters = desposition._parameters;
    return *this;
}

const Parameter& Disposition::operator[](const size_t& i) const {
    return _parameters[i];
}

const std::string& Disposition::type() const {
    return _type;
}

const std::vector<Parameter>& Disposition::parameters() const {
    return _parameters;
}

void Disposition::set_type(const std::string& type) {
    _type = type;
}

void Disposition::set_parameters(const std::vector<Parameter>& parameters) {
    _parameters.insert(_parameters.begin(), parameters.begin(),
                       parameters.end());
}

void Disposition::parse(const std::string& source) {
    _parser = Parse(source);

    if (!_parser.check(TOKEN))
        throw std::runtime_error("content-desposition needed.");
    if (Request::str_to_lower(_parser.peek().lexeme()) != "content-disposition")
        throw std::runtime_error("content-disposition needed.");
    _parser.advance();
    _parser.consume(COLON, "missing colon.");
    skip_white_spaces();
    if (_parser.check(TOKEN))
        _type = _parser.advance().lexeme();
    else
        _type = "text/plain";
    while (!_parser.is_at_end() && !_parser.check(CR_LF)) {
        _parser.consume(SEMICOLON, "missing semicolon.");
        parameter();
    }
    _parser.consume(CR_LF, "missing CR_LF");
}

void Disposition::parameter() {
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

void Disposition::skip_white_spaces() {
    while (_parser.match(SP) || _parser.match(HT))
        ;
}
