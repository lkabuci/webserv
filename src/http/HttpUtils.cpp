#include "HttpUtils.hpp"

#define SPACES " \t\r\n"

std::string HttpUtils::trim(const std::string& str) {
    std::string trimmedStr = str;
    size_t      start = trimmedStr.find_first_not_of(SPACES);
    size_t      end = trimmedStr.find_last_not_of(SPACES);
    if (start != std::string::npos && end != std::string::npos) {
        trimmedStr = trimmedStr.substr(start, end - start + 1);
    } else {
        trimmedStr.clear();
    }
    return trimmedStr;
}

bool HttpUtils::isAllWhiteSpace(const std::string& line) {
    for (std::string::const_iterator it = line.begin(); it != line.end();
         ++it) {
        if (!std::isspace(*it)) {
            return false;
        }
    }
    return true;
}
