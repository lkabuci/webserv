#pragma once

#ifndef __MULTIPART_BODY_HPP__
#define __MULTIPART_BODY_HPP__

#include "Disposition.hpp"

struct Multipart;

class MultipartBody {
  public:
    MultipartBody();
    MultipartBody(const Disposition& desposition, const ContentType& type);
    MultipartBody(const MultipartBody& form);
    ~MultipartBody();

    MultipartBody& operator=(const MultipartBody& form);

    void parse(Parse& parser, Multipart& boundary);

    const Disposition& get_desposition() const;
    const ContentType& get_type() const;
    const std::string& get_octet() const;
    std::string        get_file_name() const;

    void set_desposition(const Disposition& desposition);
    void set_type(const ContentType& type);

  private:
    Disposition _desposition;
    ContentType _type;
    std::string _octets;
};

#endif
