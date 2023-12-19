#ifndef __HTTP_UTILS_HPP__
#define __HTTP_UTILS_HPP__

#include <iostream>

class HttpUtils {
    public:
    static std::string trim(const std::string& str);
    static bool isAllWhiteSpace(const std::string& line);
};

#endif // __HTTP_UTILS_HPP__
