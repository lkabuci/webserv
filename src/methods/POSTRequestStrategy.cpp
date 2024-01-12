#include "POSTRequestStrategy.hpp"
#include "../http/Request.hpp"

void PostRequestStrategy::handleRequest(const Request& request) {
    parse_request(request);
    for (size_t i = 0; i < _headers.size(); ++i) {
        if (_headers[i].name == "Content-Type") {
            Headers* header = new ContentType();
            header->parse(_headers[i].value);
            std::cout << header->type() << "->" << header->subtype() << '\n';
            _content_types.push_back(header);
            ContentType* p = static_cast<ContentType*>(header);
            for (size_t i = 0; i < p->parameters().size(); ++i)
                std::cout << (*p)[i].attribute() << "=" << (*p)[i].value()
                          << '\n';
        }
    }
}

PostRequestStrategy::~PostRequestStrategy() {
    for (size_t i = 0; i < _content_types.size(); ++i)
        delete _content_types[i];
}

PostRequestStrategy::PostRequestStrategy(ClientEventHandler* pHandler)
    : _pHandler(pHandler) {
    init_headers();
}

void PostRequestStrategy::parse_request(const Request& request) {
    _parser = Parse(request.getRequestStr());
    //_scanner = Scanner(request.getRequestStr());
    //_token = _scanner.get_next_token();

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

void PostRequestStrategy::request_line() {
    while (!_parser.check(END) && !_parser.check(CR_LF))
        _parser.advance();
}

void PostRequestStrategy::message_header() {
    if (_parser.check(CR_LF))
        return;
    std::string name = _parser.advance().lexeme();

    _parser.consume(COLON, "missing colon");
    _field.name = name;
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
    _headers.push_back(_field);
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

void PostRequestStrategy::multipart_body() {}

void PostRequestStrategy::init_headers() {
    insert_general_headers();
    insert_request_headers();
    insert_entity_headers();
}

void PostRequestStrategy::insert_general_headers() {
    Request::general_headers.insert("Cache-Control");
    Request::general_headers.insert("Date");
    Request::general_headers.insert("Pragma");
    Request::general_headers.insert("Trailer");
    Request::general_headers.insert("Transfer-Encoding");
    Request::general_headers.insert("Upgrade");
    Request::general_headers.insert("Via");
    Request::general_headers.insert("Warning");
}

void PostRequestStrategy::insert_request_headers() {
    Request::request_headers.insert("Accept");
    Request::request_headers.insert("Accept-Charset");
    Request::request_headers.insert("Accept-Encoding");
    Request::request_headers.insert("Accept-Language");
    Request::request_headers.insert("Authorization");
    Request::request_headers.insert("Expect");
    Request::request_headers.insert("From");
    Request::request_headers.insert("Host");
    Request::request_headers.insert("If-Match");
    Request::request_headers.insert("If-Modified-Since");
    Request::request_headers.insert("If-Non-Match");
    Request::request_headers.insert("If-Range");
    Request::request_headers.insert("If-Unmodified-Since");
    Request::request_headers.insert("Max-Forwards");
    Request::request_headers.insert("Proxy-Authorization");
    Request::request_headers.insert("Range");
    Request::request_headers.insert("Referer");
    Request::request_headers.insert("TE");
    Request::request_headers.insert("User-Agent");
}

void PostRequestStrategy::insert_entity_headers() {
    Request::entity_headers.insert("Allow");
    Request::entity_headers.insert("Content-Encoding");
    Request::entity_headers.insert("Content-Language");
    Request::entity_headers.insert("Content-Length");
    Request::entity_headers.insert("Content-Location");
    Request::entity_headers.insert("Content-MD5");
    Request::entity_headers.insert("Content-Range");
    Request::entity_headers.insert("Content-Type");
    Request::entity_headers.insert("Expires");
    Request::entity_headers.insert("Last-Modified");
}
