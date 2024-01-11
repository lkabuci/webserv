#include "POSTRequestStrategy.hpp"

void PostRequestStrategy::handleRequest(const Request& request) {}

PostRequestStrategy::~PostRequestStrategy() {}

PostRequestStrategy::PostRequestStrategy(ClientEventHandler* pHandler)
    : _pHandler(pHandler) {}
