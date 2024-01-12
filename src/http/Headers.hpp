#pragma once

#ifndef __HEADERS_HPP__
#define __HEADERS_HPP__

#include "../../include/webserv.hpp"
#include "../Scanner/Parse.hpp"

class Headers {
  public:
    Headers();
    Headers(const std::string& type, const std::string& subtype);
    Headers(const Headers& header);
    virtual ~Headers(){};

    Headers& operator=(const Headers& header);

    virtual void parse(const std::string& header) = 0;

    const std::string& type() const;
    const std::string& subtype() const;

    void set_type(const std::string& type);
    void set_subtype(const std::string& subtype);

  protected:
    Parse       _parser;
    std::string _type;
    std::string _subtype;
};

#endif
