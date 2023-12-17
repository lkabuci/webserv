#pragma once

#ifndef __HTTP_CONFIG_HPP__
#define __HTTP_CONFIG_HPP__

#include "Parser.hpp"

class   HttpConfig {
public:
    HttpConfig();
    HttpConfig(const size_t& port, const std::string& domainName,
            const std::string& rootDir,
            const std::vector<std::string>& indexFiles,
            const std::map<size_t, std::string>& errorPages);
    HttpConfig(const HttpConfig& conf);
    virtual ~HttpConfig() = 0;

    HttpConfig& operator=(const HttpConfig& conf);

    const size_t&                           getPort() const;
    const std::string&                      getDomainName() const;
    const std::string&                      getRootDir() const;
    const std::vector<std::string>&         getIndexFiles() const;
    const std::map<size_t, std::string>&    getErrorPages() const;
    const std::string                   getErrorPageByCode(size_t code);

    void    setPort(const size_t& port);
    void    setDomainName(const std::string& domainName);
    void    setRootDir(const std::string& rootDir);
    void    setIndexFiles(const std::vector<std::string>& indexFiles);
    void    setErrorPages(const std::map<size_t, std::string>& errorPages);

    void    addIndexFile(const std::string& file);
    void    addErrorPage(const size_t& code, const std::string& file);

    void    display() const;

private:
    size_t                          _port;
    std::string                     _domainName;
    std::string                     _rootDir;
    std::vector<std::string>        _indexFiles;
    std::map<size_t, std::string>   _errorPages;

    virtual void    showPort() const;
    virtual void    showDomainName() const;
    virtual void    showRootDir() const;
    virtual void    showIndexFiles() const;
    virtual void    showErrorPages() const;
};

class   LocationConfig : public HttpConfig {
public:
    LocationConfig();
    LocationConfig(const size_t& port, const std::string& domainName,
                const std::string& rootDir,
                const std::vector<std::string>& indexFiles,
                const std::map<size_t, std::string>& errorPages);
    LocationConfig(const LocationConfig& lconf);
    virtual ~LocationConfig();

    LocationConfig&   operator=(const LocationConfig& lconf);

};

class   ServerConfig : public HttpConfig {
public:
    ServerConfig();
    ServerConfig(const LocationConfig& lconf, const size_t& port,
                const std::string& domainName, const std::string& rootDir,
                const std::vector<std::string>& indexFiles,
                const std::map<size_t, std::string>& errorPages);
    ServerConfig(const ServerConfig& svconf);
    virtual ~ServerConfig();

    ServerConfig&   operator=(const ServerConfig& svconf);

private:
    LocationConfig  _locationConf;
};

#endif
