#include "ConfigInfo.hpp"

ConfigInfo::ConfigInfo()
    : _port(5050)
    , _host("_")
    , _clientMaxBodySize(1)
    , _errorPage()
    , _rootDir(".")
    , _autoIndex(false)
{
    _indexFile.push_back("index.html");
}

ConfigInfo::ConfigInfo(const size_t& port, const std::string& host,
                    const size_t& clientMaxBodySize,
                    const std::vector<std::string>& errorPage,
                    const std::vector<std::string>& indexFile,
                    const std::string& rootDir,
                    bool autoIndex)
    : _port(port)
    , _host(host)
    , _clientMaxBodySize(clientMaxBodySize)
    , _errorPage(errorPage)
    , _indexFile(indexFile)
    , _rootDir(rootDir)
    , _autoIndex(autoIndex)
{
}

ConfigInfo::ConfigInfo(const ConfigInfo& svconfig)
    : _port(svconfig._port)
    , _host(svconfig._host)
    , _clientMaxBodySize(svconfig._clientMaxBodySize)
    , _errorPage(svconfig._errorPage)
    , _indexFile(svconfig._indexFile)
    , _rootDir(svconfig._rootDir)
    , _autoIndex(svconfig._autoIndex)
{
}

ConfigInfo::~ConfigInfo() {}

ConfigInfo&   ConfigInfo::operator=(const ConfigInfo &svconfig) {
    if (this == & svconfig)
        return *this;
    _port = svconfig._port;
    _host = svconfig._host;
    _clientMaxBodySize = svconfig._clientMaxBodySize;
    _errorPage = svconfig._errorPage;
    _indexFile = svconfig._indexFile;
    _rootDir = svconfig._rootDir;
    _autoIndex = svconfig._autoIndex;
    return *this;
}

void    ConfigInfo::setPort(const size_t &port) {
    _port = port;
}

void    ConfigInfo::setHost(const std::string &host) {
    _host = host;
}

void    ConfigInfo::setClientMaxBodySize(const size_t &size) {
    _clientMaxBodySize = size;
}

void    ConfigInfo::setErrorPage(const std::vector<std::string> &errorPage) {
    _errorPage = errorPage;
}

void    ConfigInfo::setIndexFile(const std::vector<std::string> &indexFile) {
    _indexFile = indexFile;
}

void    ConfigInfo::setRootDir(const std::string &rootDir) {
    _rootDir = rootDir;
}

void    ConfigInfo::setAutoIndexOn() {
    _autoIndex = true;
}

void    ConfigInfo::setAutoIndexOff() {
    _autoIndex = false;
}

const size_t&   ConfigInfo::getPort() const {
    return _port;
}

const std::string&  ConfigInfo::getHost() const {
    return _host;
}

const size_t    ConfigInfo::getClientMaxBodySize() const {
    return _clientMaxBodySize;
}

const std::vector<std::string>& ConfigInfo::getErrorPage() const {
    return _errorPage;
}

const std::vector<std::string>& ConfigInfo::getIndexFile() const {
    return _indexFile;
}

const std::string&  ConfigInfo::getRootDir() const {
    return _rootDir;
}

const bool&  ConfigInfo::getAutoIndex() const {
    return _autoIndex;
}
