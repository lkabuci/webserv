#pragma once

#include "IRequestStrategy.hpp"

class PostRequestStrategy : public IRequestStrategy {
  public:
    void handleRequest(const Request& request);

    virtual ~PostRequestStrategy();
};
