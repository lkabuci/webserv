#pragma once

#include "IRequestStrategy.hpp"

class DELETERequestStrategy : public IRequestStrategy {
  public:
    void handleRequest(const Request& request);

    virtual ~DELETERequestStrategy();
};
