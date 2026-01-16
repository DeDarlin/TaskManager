#pragma once
#include <string>

const int x = 45, y = 12;

namespace utils
{
    size_t CountLines(const std::string& filename);

    void RemoveLine(const std::string& filename, std::string line);

    void RemoveLine(const std::string& filename, int pos);

    void ChangeLine(const std::string& filename, int pos, std::string line);

    std::string RemoveSpaces(const std::string s);
}