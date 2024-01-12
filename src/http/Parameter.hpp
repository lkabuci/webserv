#pragma once

#ifndef __PARAMTER_HPP__
#define __PARAMTER_HPP__

#include "../../include/webserv.hpp"

class Parameter {
  public:
    Parameter();
    Parameter(const std::string& attribute, const std::string& value);
    Parameter(const Parameter& parameter);
    Parameter& operator=(const Parameter& parameter);

    const std::string& attribute() const;
    const std::string& value() const;

    void set_attribute(const std::string& attribute);
    void set_value(const std::string& value);

  private:
    std::string _attribute;
    std::string _value;
};

#endif
