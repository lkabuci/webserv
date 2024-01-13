#pragma once

#ifndef __DESPOSITION_HPP__
#define __DESPOSITION_HPP__

#include "../http/ContentType.hpp"

class Disposition {
  public:
    Disposition();
    Disposition(const std::string& source);
    Disposition(const std::string& type, const std::vector<Parameter>& param);
    Disposition(const Disposition& desposition);

    ~Disposition();

    Disposition&     operator=(const Disposition& desposition);
    const Parameter& operator[](const size_t& i) const;

    void parse(const std::string& source);

    const std::string&            type() const;
    const std::vector<Parameter>& parameters() const;

    void set_type(const std::string& type);
    void set_parameters(const std::vector<Parameter>& param);

  private:
    Parse                  _parser;
    std::string            _type;
    std::vector<Parameter> _parameters;

    void parameter();
    void skip_white_spaces();
};

#endif
