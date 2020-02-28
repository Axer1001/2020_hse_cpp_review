#include <fstream>
#include <iostream>
#include <list>

class Vim {
private:
    std::list<char> text;
    std::list<char>::iterator pos = text.begin();
    bool insertMode = false;

public:
    void insert(const std::string& a) {
        for (char c : a) {
            text.insert(pos, c);
        }
    }
    bool insertM() {
        return insertMode;
    }
    void i() {
        insertMode = true;
    }
    void esc() {
        insertMode = false;
    }
    void h() {
        if (pos != text.begin()) {
            --pos;
        }
    }
    void l() {
        if (pos != text.end()) {
            ++pos;
        }
    }
    void print() const {
        for (char c : text) {
            std::cout << c;
        }
        std::cout << '\n';
    }
};

int main() {
    std::fstream fileIn("input.txt", std::fstream::in);

    std::string line;
    std::getline(fileIn, line);

    Vim vim;
    size_t last_pos = 0;

    std::cin >> line;
    std::string delimiter = "<ESC>";

    while (last_pos != line.size()) {
        if (line.find(delimiter, last_pos) == std::string::npos && vim.insertM()) {
            vim.insert(line.substr(last_pos));
            break;
        }
        if (vim.insertM()) {
            vim.insert(line.substr(last_pos, line.find(delimiter, last_pos) - last_pos));
            last_pos = line.find(delimiter, last_pos) + 5;
            vim.esc();
            continue;
        } else if (line[last_pos] == 'i') {
            vim.i();
        } else if (line[last_pos] == 'h') {
            vim.h();
        } else if (line[last_pos] == 'l') {
            vim.l();
        }
        last_pos++;
    }

    vim.print();
}

