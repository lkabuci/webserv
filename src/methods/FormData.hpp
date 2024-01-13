#pragma once

#ifndef __FORM_DATA_HPP__
#define __FORM_DATA_HPP__

#include "MultipartBody.hpp"

struct Multipart;

class FormData {
  public:
    FormData();
    FormData(const Disposition& desposition, const ContentType& type);
    FormData(const FormData& form);
    ~FormData();

    FormData&            operator=(const FormData& form);
    const MultipartBody& operator[](const size_t& i) const;

    void parse(Parse& parser, Multipart& boundary);

    const std::vector<MultipartBody>& get_parts() const;

  private:
    std::vector<MultipartBody> _parts;

    void delimeter(Parse& parser, Multipart& boundary);
};

#endif
