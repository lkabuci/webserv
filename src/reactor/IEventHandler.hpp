#pragma once

class IEventHandler {
  public:
    virtual void handleEvent() = 0;
    virtual ~IEventHandler(){};
};
