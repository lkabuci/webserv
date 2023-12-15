#ifndef __HTTP_HPP__
#define __HTTP_HPP__

#define CRLF "\r\n"

namespace HTTP {
enum METHOD { GET, POST, PUT, DELETE };

enum VERSION { HTTP_1_0, HTTP_1_1, HTTP_2_0 };
} // namespace HTTP

#endif
