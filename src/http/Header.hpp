#ifndef __HEADER_HPP__
#define __HEADER_HPP__

#define CRLF "\r\n"

#include <algorithm>
#include <sstream>
#include <string>

class Header {
  public:
    Header(const std::string& key, const std::string& value);
    std::string   serialize() const;
    static Header deserialize(const std::string& header);

    const std::string& getKey() const;
    const std::string& getValue() const;
    void               setKey(const std::string&);
    void               setValue(const std::string&);

  private:
    std::string _key;
    std::string _value;
};

#endif // __HEADER_HPP__
