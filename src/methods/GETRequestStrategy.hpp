#pragma once

#include "../config/LocationConfig.hpp"
#include "../config/ServerConfig.hpp"
#include "../reactor/ClientEventHandler.hpp"
#include "IRequestStrategy.hpp"

class GetRequestStrategy : public IRequestStrategy {
  public:
    explicit GetRequestStrategy(ClientEventHandler* pHandler);
    void     handleRequest(const Request& request);
    virtual ~GetRequestStrategy();

  private:
    ClientEventHandler* _pHandler;

    const LocationConfig* findBestLocation(const ServerConfig& config,
                                           const std::string&  uri) const;
    bool  matchesLocation(const LocationConfig& loc,
                          const std::string&    uri) const;
    void  serveFile(const std::string& path);
    void  serveDirectory(const std::string& dirPath, const std::string& uri);
    void  serveErrorPage(int code, const ServerConfig& config);
};
