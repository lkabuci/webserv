#include "DELETERequestStrategy.hpp"

void DELETERequestStrategy::handleRequest(const Request& request) {}

DELETERequestStrategy::~DELETERequestStrategy() {}

DELETERequestStrategy::DELETERequestStrategy(ClientEventHandler* pHandler)
    : _pHandler(pHandler) {}
