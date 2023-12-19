#include "Header.hpp"
#include "HttpUtils.hpp"
#include <stdexcept>

Header::Header(const std::string& key, const std::string& value)
    : _key(key), _value(value) {}

std::string Header::serialize() const {
    std::stringstream header;
    header << _key << ": " << _value;
    return header.str();
}

Header Header::deserialize(const std::string& header) {
    size_t pos = header.find(":");
    if (pos == std::string::npos) {
        throw std::runtime_error("Error while parsing the header");
    }
    std::string key = HttpUtils::trim(header.substr(0, pos));
    std::string value = HttpUtils::trim(header.substr(pos + 1));
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
