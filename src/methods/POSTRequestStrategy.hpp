#pragma once

#include "../reactor/ClientEventHandler.hpp"
#include "IRequestStrategy.hpp"

class PostRequestStrategy : public IRequestStrategy {
  public:
    explicit PostRequestStrategy(ClientEventHandler* pHandler);
    void handleRequest(const Request& request);
    virtual ~PostRequestStrategy();

  private:
    ClientEventHandler* _pHandler;
};
