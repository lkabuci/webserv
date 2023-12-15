#include "Header.hpp"
#include <stdexcept>

Header::Header(const std::string& key, const std::string& value)
    : _key(key), _value(value) {}

std::string Header::serialize() const {
    std::stringstream header;
    header << _key << ": " << _value << CRLF;
    return header.str();
}

Header Header::deserialize(const std::string& header) {
    size_t pos = header.find(": ");
    if (pos == std::string::npos) {
        throw std::runtime_error("Error while parsing the header");
    }
    std::string key = header.substr(0, pos);
    std::string value = header.substr(pos + 2); // NOTE: what about \r\n?
    return Header(key, value);
}

const std::string& Header::getKey() const {
    return _key;
}

const std::string& Header::getValue() const {
    return _value;
}

void Header::setKey(const std::string& key) {
    _key = key;
}

void Header::setValue(const std::string& value) {
    _value = value;
}
