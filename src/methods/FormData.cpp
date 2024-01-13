#include "FormData.hpp"
#include "POSTRequestStrategy.hpp"

FormData::FormData() {}

FormData::FormData(const Disposition& desposition, const ContentType& type) {
    _parts.push_back(MultipartBody(desposition, type));
}

FormData::FormData(const FormData& form) : _parts(form._parts) {}

FormData::~FormData() {}

FormData& FormData::operator=(const FormData& form) {
    if (this == &form)
        return *this;
    _parts = form._parts;
    return *this;
}

const MultipartBody& FormData::operator[](const size_t& i) const {
    return _parts[i];
}

void FormData::parse(Parse& parser, Multipart& boundary) {
    MultipartBody part;

    do {
        part.parse(parser, boundary);
        _parts.push_back(part);
        delimeter(parser, boundary);
        part.parse(parser, boundary);
    } while (!parser.is_at_end() && !boundary.is_close_delimeter(parser));
    if (parser.previous().type() != TOKEN)
        throw std::runtime_error("missing CR_LF at end of body.");
}

void FormData::delimeter(Parse& parser, Multipart& boundary) {
    if (parser.is_at_end())
        return;
    if (!boundary.is_delimeter(parser))
        throw std::runtime_error("missing delimeter.");
    parser.advance();
    parser.consume(CR_LF, "missing CRLF.");
}
