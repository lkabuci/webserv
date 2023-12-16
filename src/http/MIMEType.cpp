#include "MIMEType.hpp"
#include <cctype>
#include <fstream>
#include <map>
#include <nl_types.h>
#include <sstream>
#include <string>
#include <vector>
#define SPACES " \t\r\n"

static std::string trim(const std::string& str);
static bool is_all_whitespace(const std::string& line);
static void removeHeader(std::string& content);

MIMEType::MIMEType() {
    const std::string mimeTypesFilePath = "../../config/mime.types";
    parseMimeTypesFile(mimeTypesFilePath);
}

void MIMEType::parseMimeTypesFile(const std::string& mimeTypesFilePath) {
    std::ifstream file("/Users/relkabou/Desktop/webserv/config/mime.types");
    std::string line;
    if (!file.is_open()) {
        throw std::runtime_error("Could not open mime.types file");
    }
    std::string fileContent((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    removeHeader(fileContent);
    std::stringstream ss(fileContent);
    while (std::getline(ss, line, ';')) {
        if (is_all_whitespace(line))
            continue;

        std::vector<std::string> mime_line = get_mime_line_info(trim(line));
        for (int i = 1; i < mime_line.size(); ++i) {
            _mime_types.insert(std::pair<std::string, std::string>(
                mime_line[i], mime_line[0]));
        }
    }
}

std::string
MIMEType::getMimeTypeForExtension(const std::string& extension) const {
    std::map<std::string, std::string>::const_iterator it;
    it = _mime_types.find(extension);
    if (it != _mime_types.end()) {
        return it->second;
    }
    return "text/plain";
}

std::vector<std::string> MIMEType::get_mime_line_info(std::string line) {
    std::string buffer;
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
    content = trim(content);

    size_t start = content.find("{");
    if (start == std::string::npos || start == 0) {
        throw std::runtime_error("Invalid mime.types file");
    }

    std::string beforeBrace = trim(content.substr(0, start));
    if (beforeBrace != "types") {
        throw std::runtime_error("Invalid mime.types file");
    }

    size_t end = content.rfind("}");
    if (end == std::string::npos || start >= end) {
        throw std::runtime_error("Invalid mime.types file");
    }
    content = content.substr(start + 1, end - start - 1);
}

static std::string trim(const std::string& str) {
    std::string trimmedStr = str;
    size_t start = trimmedStr.find_first_not_of(SPACES);
    size_t end = trimmedStr.find_last_not_of(SPACES);
    if (start != std::string::npos && end != std::string::npos) {
        trimmedStr = trimmedStr.substr(start, end - start + 1);
    } else {
        trimmedStr.clear();
    }
    return trimmedStr;
}

bool is_all_whitespace(const std::string& line) {
    for (std::string::const_iterator it = line.begin(); it != line.end();
         ++it) {
        if (!std::isspace(*it)) {
            return false;
        }
    }
    return true;
}
