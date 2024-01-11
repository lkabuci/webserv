#include "GETRequestStrategy.hpp"

GetRequestStrategy::GetRequestStrategy(ClientEventHandler* pHandler)
    : _pHandler(pHandler) {
    _pHandler->setIsDoneReading(true);
    std::cout << "Client: " << _pHandler->getClient().getClientAddress()
              << " sent." << std::endl;
    std::cout << _pHandler->getHeader() << std::endl;
}

void GetRequestStrategy::handleRequest(const Request& request) {}

GetRequestStrategy::~GetRequestStrategy() {}
