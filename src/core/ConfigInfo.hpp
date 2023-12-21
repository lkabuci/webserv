#pragma once

#ifndef __CONFIG_INFO_HPP__
#define __CONFIG_INFO_HPP__

#include "common.hpp"

class ConfigInfo {
public:
    ConfigInfo();
    ConfigInfo(const size_t& port, const std::string& host,
                const size_t& clientMaxBodySize,
                const std::vector<std::string>& errorPage,
                const std::string& indexFile, const std::string& rootDir,
                bool autoIndex);
    ConfigInfo(const ConfigInfo& svconfig);
    virtual ~ConfigInfo();

    ConfigInfo&   operator=(const ConfigInfo& svconfig);

    void    setPort(const size_t& port);
    void    setHost(const std::string& host);
    void    setClientMaxBodySize(const size_t& size);
    void    setErrorPage(const std::vector<std::string>& errorPage);
    void    setIndexFile(const std::vector<std::string>& indexFile);
    void    setRootDir(const std::string& rootDir);
    void    setAutoIndexOn();
    void    setAutoIndexOff();

    const size_t&                   getPort() const;
    const std::string&              getHost() const;
    const size_t                    getClientMaxBodySize() const;
    const std::vector<std::string>& getErrorPage() const;
    const std::vector<std::string>& getIndexFile() const;
    const std::string&              getRootDir() const;
    const bool&                     getAutoIndex() const;

protected:
    size_t                      _port;
    std::string                 _host;
    size_t                      _clientMaxBodySize;
    std::vector<std::string>    _errorPage;
    std::vector<std::string>    _indexFile;
    std::string                 _rootDir;
    bool                        _autoIndex;
};

#endif
