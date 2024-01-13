#include "MultipartBody.hpp"
#include "POSTRequestStrategy.hpp"

MultipartBody::MultipartBody() {}

MultipartBody::MultipartBody(const Disposition& desposition,
                             const ContentType& type)
    : _desposition(desposition), _type(type) {}

MultipartBody::MultipartBody(const MultipartBody& form)
    : _desposition(form._desposition), _type(form._type) {}

MultipartBody::~MultipartBody() {}

MultipartBody& MultipartBody::operator=(const MultipartBody& form) {
    if (this == &form)
        return *this;
    _desposition = form._desposition;
    _type = form._type;
    return *this;
}

const Disposition& MultipartBody::get_desposition() const {
    return _desposition;
}

const ContentType& MultipartBody::get_type() const {
    return _type;
}

const std::string& MultipartBody::get_octet() const {
    return _octets;
}

void MultipartBody::set_desposition(const Disposition& desposition) {
    _desposition = desposition;
}

void MultipartBody::set_type(const ContentType& type) {
    _type = type;
}

void MultipartBody::parse(Parse& parser, Multipart& boundary) {
    _desposition.parse(parser.get_line());
    if (Request::str_to_lower(parser.peek().lexeme()) == "content-type")
        _type.parse(parser.get_line());
    parser.consume(CR_LF, "missing CRLF.");
    while (!parser.is_at_end() && !parser.check(CR_LF)) {
        if (boundary.is_delimeter(parser))
            break;
        _octets.append(parser.advance().lexeme());
    }
}

std::string MultipartBody::get_file_name() const {
    for (size_t i = 0; i < _desposition.parameters().size(); ++i) {
        if (_desposition[i].attribute() == "filename")
            return _desposition[i].value();
    }
    return "nofile";
}
