#ifndef __MIME_TYPE_HPP__
#define __MIME_TYPE_HPP__

#include <string>
#include <vector>

#include <map>
class MIMEType {
  public:
    MIMEType(const std::string& path = "");
    std::string getMimeTypeForExtension(const std::string& extension) const;

  private:
    std::map<std::string, std::string> _mimeTypes;
    void parseMimeTypesFile(const std::string& mimeTypesFilePath);
    std::vector<std::string> getMimeLineInfo(std::string line);
};

#endif // __MIME_TYPE_HPP__
