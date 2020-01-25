#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::string temp;
    std::vector<std::string> splitted;
    for (const auto& c : str) {
        if (c != delimiter) {
            temp.push_back(c);
        } else {
            splitted.push_back(temp);
            temp = "";
        }
    }
    splitted.push_back(temp);
    return splitted;
}

