#pragma once

#ifndef __HTTP_CONFIG_HPP__
#define __HTTP_CONFIG_HPP__

#include "Parser.hpp"

class   HttpConfig {
public:
    typedef std::map<std::string, std::vector<size_t> > keyVector;
    HttpConfig();
    HttpConfig(const size_t& port, const std::vector<std::string>& domainName,
            const std::string& rootDir,
            const std::vector<std::string>& indexFiles,
            const keyVector& errorPages);
    HttpConfig(const HttpConfig& conf);
    virtual ~HttpConfig() = 0;

    HttpConfig& operator=(const HttpConfig& conf);

    const size_t&                   getPort() const;
    const std::vector<std::string>& getDomainName() const;
    const std::string&              getRootDir() const;
    const std::vector<std::string>& getIndexFiles() const;
    const keyVector&                getErrorPages() const;

    void    setPort(const size_t& port);
    void    setDomainName(const std::vector<std::string>& domainName);
    void    setRootDir(const std::string& rootDir);
    void    setIndexFiles(const std::vector<std::string>& indexFiles);
    void    setErrorPages(const keyVector& errorPages);

    void    display() const;

private:
    size_t                      _port;
    std::vector<std::string>    _domainName;
    std::string                 _rootDir;
    std::vector<std::string>    _indexFiles;
    keyVector                   _errorPages;

    virtual void    showClassName() const;
    void    showPort() const;
    void    showDomainName() const;
    void    showRootDir() const;
    void    showIndexFiles() const;
    void    showErrorPages() const;
};

class   LocationConfig : public HttpConfig {
public:
    LocationConfig(const std::string& path);
    LocationConfig(const std::string& path, const size_t& port,
                const std::vector<std::string>& domainName,
                const std::string& rootDir,
                const std::vector<std::string>& indexFiles,
                const keyVector& errorPages);
    LocationConfig(const LocationConfig& lconf);
    virtual ~LocationConfig();

    LocationConfig&   operator=(const LocationConfig& lconf);

    virtual void    showClassName() const;

    void                addPath(const std::string& path);
    const std::string&  getPath() const;

private:
    std::string _path;
};

class   ServerConfig : public HttpConfig {
public:
    ServerConfig();
    ServerConfig(const std::vector<LocationConfig>& lconf, const size_t& port,
                const std::vector<std::string>& domainName,
                const std::string& rootDir,
                const std::vector<std::string>& indexFiles,
                const keyVector& errorPages);
    ServerConfig(const ServerConfig& svconf);
    virtual ~ServerConfig();

    ServerConfig&   operator=(const ServerConfig& svconf);

    virtual void    showClassName() const;


    void    addLocation(const LocationConfig& lconf);
    std::vector<LocationConfig>&   getLocations();

    void    addLocationPath(const std::string& path, size_t pos);
    const std::string&  getLocationPath(size_t pos) const;

private:
    std::vector<LocationConfig> _locationConf;
};

#endif
