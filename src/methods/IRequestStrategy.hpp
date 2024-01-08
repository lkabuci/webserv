#pragma once

class Request;

class IRequestStrategy {
  public:
    virtual void handleRequest(const Request& request) = 0;

    virtual ~IRequestStrategy(){};
};
