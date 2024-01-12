#pragma once

#ifndef __CONTENT_TYPE_HPP__
#define __CONTENT_TYPE_HPP__

#include "../Scanner/Parse.hpp"
#include "../http/Headers.hpp"
#include "../http/Parameter.hpp"

class ContentType : public Headers {
  public:
    enum { MULTIPART };

    ContentType();

    virtual void parse(const std::string& header);
    void         add(const Parameter& parameter);
    void         insert(const std::vector<Parameter>& items);

    const std::vector<Parameter>& parameters() const;
    const Parameter&              operator[](const size_t& i) const;

  private:
    std::vector<Parameter> _parameters;
    void                   parameter();
};

#endif
