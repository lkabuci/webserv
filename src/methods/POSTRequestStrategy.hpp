#pragma once

#include "../Scanner/Parse.hpp"
#include "../http/ContentType.hpp"
#include "../reactor/ClientEventHandler.hpp"
#include "FormData.hpp"
#include "IRequestStrategy.hpp"

enum ContentTypes { MULTIPART };

struct Multipart {
    std::string boundary;
    std::string delimeter;
    std::string close_delimeter;

    bool is_delimeter(Parse& parser);
    bool is_close_delimeter(Parse& parser);
};

class PostRequestStrategy : public IRequestStrategy {
  public:
    explicit PostRequestStrategy(ClientEventHandler* pHandler);
    void handleRequest(const Request& request);
    virtual ~PostRequestStrategy();

    enum { MAX_BOUNDARY_LENGTH = 70 };

  private:
    ClientEventHandler*   _pHandler;
    std::vector<Headers*> _headers;
    Multipart             _boundary;
    ContentTypes          _type;
    // std::string           _length;
    std::string _body;
    Parse       _parser;
    FormData    _form_data;

    struct Header_Fields {
        std::string name;
        std::string value;
    } _field;
    std::vector<Header_Fields> _header_fields;

    void parse_request(const Request& request);
    void parse_headers();
    void parse_body();
    void request_line();
    void message_header();
    void message_body();
    void field_value();
    bool field_content();
    bool linear_white_space();
    void skip_spaces();
    void general_header();
    void request_header();
    void entity_header();

    ContentTypes content_type();
    void         set_length();
    void         set_boundary();
    void         multipart_body(Headers* header);
    void         body_part();
    void         preamble();

    bool line_contains_boundary();
};
