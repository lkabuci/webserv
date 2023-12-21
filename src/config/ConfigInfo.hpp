#pragma once

#ifndef __CONFIG_INFO_HPP__
#define __CONFIG_INFO_HPP__

#include "common.hpp"

class ConfigInfo {
public:
    ConfigInfo();
    ConfigInfo(const size_t& port, const std::string& serverName,
                const size_t& clientMaxBodySize,
                const std::vector<std::string>& errorPage,
                const std::vector<std::string>& indexFiles,
                const std::string& rootDir,
                bool autoIndex);
    ConfigInfo(const ConfigInfo& svconfig);
    virtual ~ConfigInfo();

    ConfigInfo&   operator=(const ConfigInfo& svconfig);

    void    setPort(const size_t& port);
    void    setServerName(const std::string& serverName);
    void    setClientMaxBodySize(const size_t& size);
    void    setErrorPage(const std::vector<std::string>& errorPage);
    void    setIndexFiles(const std::vector<std::string>& indexFiles);
    void    setRootDir(const std::string& rootDir);
    void    setAutoIndexOn();
    void    setAutoIndexOff();

    const size_t&                   getPort() const;
    const std::string&              getServerName() const;
    const size_t                    getClientMaxBodySize() const;
    const std::vector<std::string>& getErrorPage() const;
    const std::vector<std::string>& getIndexFiles() const;
    const std::string&              getRootDir() const;
    const bool&                     getAutoIndex() const;

protected:
    size_t                      _port;
    std::string                 _serverName;
    size_t                      _clientMaxBodySize;
    std::vector<std::string>    _errorPage;
    std::vector<std::string>    _indexFiles;
    std::string                 _rootDir;
    bool                        _autoIndex;
};

#endif
