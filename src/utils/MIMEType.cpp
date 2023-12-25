#include "MIMEType.hpp"
#include "../http/HttpUtils.hpp"
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

static void removeHeader(std::string& content);

// NOTE: this script should be run from the root of the repo
MIMEType::MIMEType(const std::string& path) {
    if (path.empty()) {
        const char* rootDirectory = std::getenv("PWD");
        parseMimeTypesFile(std::string(rootDirectory) + "/config/mime.types");
        return;
    }
    parseMimeTypesFile(path);
}

void MIMEType::parseMimeTypesFile(const std::string& mimeTypesFilePath) {
    std::ifstream file(mimeTypesFilePath.c_str());
    std::string   line;
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the mime.types file. Check if "
                                 "the file exists and has proper permissions.");
    }
    std::string fileContent((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    file.close();
    removeHeader(fileContent);
    std::stringstream ss(fileContent);
    while (std::getline(ss, line, ';')) {
        if (HttpUtils::isAllWhiteSpace(line))
            continue;

        std::vector<std::string> mime_line =
            getMimeLineInfo(HttpUtils::trim(line));
        for (int i = 1; i < mime_line.size(); ++i) {
            _mimeTypes.insert(std::pair<std::string, std::string>(
                mime_line[i], mime_line[0]));
        }
    }
}

std::string
MIMEType::getMimeTypeForExtension(const std::string& extension) const {
    std::map<std::string, std::string>::const_iterator it;
    it = _mimeTypes.find(extension);
    if (it != _mimeTypes.end()) {
        return it->second;
    }
    return "text/plain";
}

std::vector<std::string> MIMEType::getMimeLineInfo(std::string line) {
    std::string              buffer;
    std::vector<std::string> lineInfo;

    std::stringstream ss(line);
    while (std::getline(ss, buffer, ' ')) {
        if (buffer.empty())
            continue;
        lineInfo.push_back(buffer);
    }
    return lineInfo;
}

// Check if the string before "{" is "types" only
// Remove the "types {" and "}" from the end
void removeHeader(std::string& content) {
    const std::string mimeDirectiveName = "types";
    content = HttpUtils::trim(content);

    size_t start = content.find("{");
    if (start == std::string::npos || start == 0) {
        throw std::runtime_error(
            "Invalid header format in the mime.types file. Ensure the file "
            "starts with 'types {'.");
    }

    std::string beforeBrace = HttpUtils::trim(content.substr(0, start));
    if (beforeBrace != mimeDirectiveName) {
        throw std::runtime_error(
            "Invalid header format in the mime.types file. Ensure the file "
            "have the 'types' directive.");
    }

    size_t end = content.rfind("}");
    if (end == std::string::npos || start >= end) {
        throw std::runtime_error(
            "Invalid header format in the mime.types file. Ensure the file "
            "ends with the '}'");
    }
    content = content.substr(start + 1, end - start - 1);
}
