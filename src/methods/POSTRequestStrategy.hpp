#pragma once

#include "../Scanner/Parse.hpp"
#include "../http/ContentType.hpp"
#include "../reactor/ClientEventHandler.hpp"
#include "IRequestStrategy.hpp"

enum ContentTypes { MULTIPART };

class PostRequestStrategy : public IRequestStrategy {
  public:
    explicit PostRequestStrategy(ClientEventHandler* pHandler);
    void handleRequest(const Request& request);
    virtual ~PostRequestStrategy();

    enum { MAX_BOUNDARY_LENGTH = 70 };

  private:
    ClientEventHandler*   _pHandler;
    std::vector<Headers*> _content_types;
    std::string           _boundary;
    std::string           _delimeter;
    std::string           _closeDelimeter;
    std::string           _type;
    std::string           _length;
    std::string           _body;
    Parse                 _parser;

    struct Header_Fields {
        std::string name;
        std::string value;
    } _field;
    std::vector<Header_Fields> _headers;

    void init_headers();
    void insert_general_headers();
    void insert_request_headers();
    void insert_entity_headers();

    void parse_request(const Request& request);
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
    void         multipart_body();
};
