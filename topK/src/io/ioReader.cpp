#include "ioReader.hpp"
#include <regex>
#include <stdexcept>

ioReader::ioReader(const std::string& filename) {
    ifs.open(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

ioReader::~ioReader() {
    if (ifs.is_open()) {
        ifs.close();
    }
}

bool ioReader::next(types::Timestamp& ts, std::string& content) {
    std::string line;
    if (!std::getline(ifs, line)) {
        return false;
    }

    static std::regex pattern(R"(\[(\d+):(\d+):(\d+)\]\s*(.*))");
    std::smatch match;

    if (std::regex_match(line, match, pattern)) {
        int h = std::stoi(match[1]);
        int m = std::stoi(match[2]);
        int s = std::stoi(match[3]);
        ts = h * 3600 + m * 60 + s;
        content = match[4];
        return true;
    }
    return false;
}

