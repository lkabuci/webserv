#ifndef WEBSERV_H
#define WEBSERV_H

#include "../src/cgi/CGIHandler.hpp"
#include "../src/handlers/BaseHandler.hpp"
#include "../src/handlers/ConnectionHandler.hpp"
#include "../src/handlers/DataHandler.hpp"
#include "../src/handlers/RequestHandler.hpp"
#include "../src/helpers/ServerHelper.hpp"
#include "../src/http/HTTP.hpp"
#include "../src/http/Header.hpp"
#include "../src/http/HttpUtils.hpp"
#include "../src/http/Request.hpp"
#include "../src/http/StatusLine.hpp"
#include "../src/reactor/Demultiplexer.hpp"
#include "../src/reactor/Dispatcher.hpp"
#include "../src/reactor/EventLoop.hpp"
#include "../src/stream/AddressResolver.hpp"
#include "../src/stream/Server.hpp"
#include "../src/stream/Socket.hpp"
#include "../src/utils/MIMEType.hpp"
#endif
