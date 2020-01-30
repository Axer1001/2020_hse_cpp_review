#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> splitted;
    size_t last_pos = 0;
    while (str.find(delimiter, last_pos) != std::string::npos) {
        splitted.push_back(str.substr(last_pos, str.find(delimiter, last_pos) - last_pos));
        last_pos = str.find(delimiter, last_pos) + 1;
    }
    splitted.push_back(str.substr(last_pos));
    return splitted;
}

