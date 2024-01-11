#pragma once

#include "../reactor/ClientEventHandler.hpp"
#include "IRequestStrategy.hpp"

class GetRequestStrategy : public IRequestStrategy {
  public:
    explicit GetRequestStrategy(ClientEventHandler* pHandler);
    void handleRequest(const Request& request);
    virtual ~GetRequestStrategy();

  private:
    ClientEventHandler* _pHandler;
};
