#pragma once

#define BUFFER_SIZE 4096
#define PORT_LEN 6

extern bool isServerRunning;

#include "../src/config/ConfigInfo.hpp"
#include "../src/config/ConfigParse.hpp"
#include "../src/config/Env.hpp"
#include "../src/config/Extractor.hpp"
#include "../src/config/Lexer.hpp"
#include "../src/config/LocationConfig.hpp"
#include "../src/config/ParseException.hpp"
#include "../src/config/Parser.hpp"
#include "../src/config/RunTimeException.hpp"
#include "../src/config/ServerConfig.hpp"
#include "../src/config/SyntaxException.hpp"
#include "../src/config/Token.hpp"
#include "../src/config/TokenType.hpp"
#include "../src/config/common.hpp"
#include "../src/helpers/ServerHelper.hpp"
#include "../src/http/HTTP.hpp"
#include "../src/http/Header.hpp"
#include "../src/http/HttpUtils.hpp"
#include "../src/http/Request.hpp"
#include "../src/http/StatusLine.hpp"
#include "../src/reactor/Webserver.hpp"
#include "../src/stream/AddressResolver.hpp"
#include "../src/stream/Client.hpp"
#include "../src/stream/Socket.hpp"
#include "../src/utils/MIMEType.hpp"
