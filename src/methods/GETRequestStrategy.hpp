#pragma once

#include "IRequestStrategy.hpp"

class GetRequestStrategy : public IRequestStrategy {
  public:
    void handleRequest(const Request& request);

    virtual ~GetRequestStrategy();
};
