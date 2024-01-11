#pragma once

#include "../reactor/ClientEventHandler.hpp"
#include "IRequestStrategy.hpp"

class DELETERequestStrategy : public IRequestStrategy {
  public:
    explicit DELETERequestStrategy(ClientEventHandler* pHandler);

    void handleRequest(const Request& request);

    virtual ~DELETERequestStrategy();

  private:
    ClientEventHandler* _pHandler;
};
