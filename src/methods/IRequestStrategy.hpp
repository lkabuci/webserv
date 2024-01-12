#pragma once

// #include "GETRequestStrategy.hpp"
// #include "POSTRequestStrategy.hpp"
// #include "DELETERequestStrategy.hpp"

#include "../Scanner/Scanner.hpp"

class Request;

class IRequestStrategy {
  public:
    virtual void handleRequest(const Request& request) = 0;

    virtual ~IRequestStrategy(){};
};
