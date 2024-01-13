#include "POSTRequestStrategy.hpp"
#include "../http/Request.hpp"

void PostRequestStrategy::handleRequest(const Request& request) {
    parse_request(request);
    parse_headers();
    parse_body();
}

PostRequestStrategy::~PostRequestStrategy() {
    for (size_t i = 0; i < _headers.size(); ++i)
        delete _headers[i];
}

PostRequestStrategy::PostRequestStrategy(ClientEventHandler* pHandler)
    : _pHandler(pHandler) {}

void PostRequestStrategy::parse_request(const Request& request) {
    _parser = Parse(request.getRequestStr());

    request_line();
    _parser.consume(CR_LF, "missing CRLF1.");
    while (!_parser.match(END) && !_parser.match(CR_LF)) {
        message_header();
        _parser.consume(CR_LF, "missing CRLF");
    }
    if (_parser.previous().type() != CR_LF)
        throw std::runtime_error("missing CRLF.");
    message_body();
}

void PostRequestStrategy::parse_headers() {
    for (size_t i = 0; i < _header_fields.size(); ++i) {
        if (_header_fields[i].name == "content-type") {
            Headers* header = new ContentType();

            header->parse(_header_fields[i].value);
            _headers.push_back(header);
            multipart_body(header);
        }
    }
}

void PostRequestStrategy::parse_body() {
    for (size_t i = 0; i < _header_fields.size(); ++i) {
        // if (_header_fields[i].name == "content-type" &&
        // dynamic_cast<ContentType*>(_headers[i])) {
        //     _headers[i]->parse(_header_fields[i].value);
        //     multipart_body(_headers[i]);
        // }
    }
}

void PostRequestStrategy::request_line() {
    while (!_parser.check(END) && !_parser.check(CR_LF))
        _parser.advance();
}

void PostRequestStrategy::message_header() {
    if (_parser.check(CR_LF))
        return;
    std::string name = _parser.advance().lexeme();

    _parser.consume(COLON, "missing colon");
    _field.name = Request::str_to_lower(name);
    field_value();
}

void PostRequestStrategy::message_body() {
    while (!_parser.match(END))
        _body.append(_parser.advance().lexeme());
}

void PostRequestStrategy::field_value() {
    if (_parser.check(CR_LF))
        return;
    std::string value;

    linear_white_space();
    skip_spaces();
    do {
        value.append(_parser.advance().lexeme());
        if (linear_white_space() && !_parser.check(CR_LF))
            value.append(" ");
    } while (field_content());
    skip_spaces();
    linear_white_space();
    _field.value = value;
    _header_fields.push_back(_field);
}

bool PostRequestStrategy::field_content() {
    switch (_parser.peek().type()) {
    case END:
    case CR_LF:
    case SP:
    case HT:
        return false;
    default:
        break;
    }
    return true;
}

bool PostRequestStrategy::linear_white_space() {
    if (!_parser.check(SP) && !_parser.check(HT))
        return false;
    while (_parser.match(SP) || _parser.match(HT))
        ;
    return true;
}

void PostRequestStrategy::skip_spaces() {
    while (_parser.match(SP) || _parser.match(HT))
        ;
}

void PostRequestStrategy::general_header() {
    // if (Request::request_headers.find(peek().lexeme()) !=
    // Request::request_headers.end())
}

void PostRequestStrategy::entity_header() {}

void PostRequestStrategy::multipart_body(Headers* header) {
    ContentType* ptr = static_cast<ContentType*>(header);

    _boundary.boundary = (*ptr)[0].value();
    if (_boundary.boundary.length() > MAX_BOUNDARY_LENGTH)
        throw std::runtime_error("boundary too large.");
    _boundary.delimeter = std::string("--") + _boundary.boundary;
    _boundary.close_delimeter = _boundary.delimeter + "--";
    _parser = Parse(_body);
    preamble();
    _parser.consume(CR_LF, "missing CRLF.");
    if (!_boundary.is_delimeter(_parser))
        throw std::runtime_error("missing boundar.");
    _parser.advance();
    _parser.consume(CR_LF, "missing CRLF.");
    body_part();
}

void PostRequestStrategy::preamble() {
    while (!_parser.check(END) && !_parser.check(CR_LF)) {
        if (_boundary.is_delimeter(_parser))
            break;
        _parser.advance();
    }
}

void PostRequestStrategy::body_part() {
    while (!_boundary.is_delimeter(_parser) && !_parser.is_at_end()) {
        _form_data.parse(_parser, _boundary);
    }
}

bool PostRequestStrategy::line_contains_boundary() {
    return _parser.peek().lexeme().find(_boundary.delimeter) !=
           std::string::npos;
}

bool Multipart::is_delimeter(Parse& parser) {
    if (parser.peek().type() == CR_LF)
        parser.advance();
    std::string str = parser.peek().lexeme();
    size_t      pos = str.find("--");

    if (pos == std::string::npos)
        return false;
    size_t i = pos + 2;
    for (size_t j = 0; i < str.length(); ++j) {
        if (str[i] != boundary[j])
            return false;
        i++;
    }
    return i == str.length();
}

bool Multipart::is_close_delimeter(Parse& parser) {
    if (parser.peek().lexeme() != close_delimeter)
        return false;
    parser.advance();
    return true;
}
