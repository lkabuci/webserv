#include "HttpConfig.hpp"

HttpConfig::HttpConfig() {}

HttpConfig::HttpConfig(const size_t& port,
                const std::vector<std::string>& domainName,
                const std::string& rootDir,
                const std::vector<std::string>& indexFiles,
                const keyVector& errorPages)
    : _port(port)
    , _domainName(domainName)
    , _rootDir(rootDir)
    , _indexFiles(indexFiles)
    , _errorPages(errorPages)
{
}

HttpConfig::HttpConfig(const HttpConfig& conf)
    : _port(conf._port)
    , _domainName(conf._domainName)
    , _rootDir(conf._rootDir)
    , _indexFiles(conf._indexFiles)
    , _errorPages(conf._errorPages)
{
}

HttpConfig::~HttpConfig() {}

HttpConfig& HttpConfig::operator=(const HttpConfig& conf) {
    if (this == &conf)
        return *this;
    _port = conf._port;
    _domainName = conf._domainName;
    _rootDir = conf._rootDir;
    _indexFiles = conf._indexFiles;
    _errorPages = conf._errorPages;
    return *this;
}

const size_t&   HttpConfig::getPort() const { return _port; }

const std::vector<std::string>&  HttpConfig::getDomainName() const {
    return _domainName;
}

const std::string&  HttpConfig::getRootDir() const { return _rootDir; }

const std::vector<std::string>& HttpConfig::getIndexFiles() const {
    return _indexFiles;
}

const HttpConfig::keyVector&  HttpConfig::getErrorPages() const {
    return _errorPages;
}

//const std::string  HttpConfig::getErrorPageByCode(int code) {
    //if (_errorPages.find(code) != _errorPages.end())
    //    return _errorPages[code];
    //return "";
//}

void    HttpConfig::setPort(const size_t& port) {
    _port = port;
}

void    HttpConfig::setDomainName(const std::vector<std::string>& domainName) {
    _domainName = domainName;
}

void    HttpConfig::setRootDir(const std::string& rootDir) {
    _rootDir = rootDir;
}

void    HttpConfig::setIndexFiles(const std::vector<std::string>& indexFiles) {
    _indexFiles = indexFiles;
}

void    HttpConfig::setErrorPages(const keyVector& errorPages)
{
    _errorPages = errorPages;
}

//void    HttpConfig::addDomainName(const std::string& name) {
//    _domainName.push_back(name);
//}

//void    HttpConfig::addIndexFile(const std::string& file) {
//    _indexFiles.push_back(file);
//}


void    HttpConfig::display() const {
    showClassName();
    showPort();
    showDomainName();
    showRootDir();
    showIndexFiles();
    showErrorPages();
}

void    HttpConfig::showClassName() const {
}

void    HttpConfig::showPort() const {
    std::cout << "Port: " << _port << std::endl;
}

void    HttpConfig::showDomainName() const {
    std::cout << "Domain Name:";
    for (size_t i = 0; i < _domainName.size(); ++i)
        std::cout << " " << _domainName[i];
    std::cout << std::endl;
}

void    HttpConfig::showRootDir() const {
    std::cout << "Root: " << _rootDir << std::endl;
}

void    HttpConfig::showIndexFiles() const {
    std::cout << "Index:";
    for (size_t i = 0; i < _indexFiles.size(); ++i)
        std::cout << " " << _indexFiles[i];
    std::cout << std::endl;
}

void    HttpConfig::showErrorPages() const {
    keyVector::const_iterator   it = _errorPages.begin();

    for (; it != _errorPages.end(); ++it) {
        std::cout << it->first << ":";
        for (size_t i = 0; i < it->second.size(); ++i)
            std::cout << " " << it->second[i];
        std::cout << "\n";
    }
}
