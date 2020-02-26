#include <iostream>
#include <set>
#include <queue>
#include <cstdint>

int main() {
    std::multiset<int64_t> window;
    std::queue<int64_t> elements;
    size_t numberOfElements, w_length;
    std::cin >> numberOfElements >> w_length;
    if (w_length <= 0) {
        return 0;
    }
    for (size_t i = 0; i < w_length; ++i) {
        int64_t element;
        std::cin >> element;
        window.insert(element);
        elements.push(element);
    }
    std::cout << *window.begin() << '\n';
    for (size_t i = w_length; i < numberOfElements; ++i) {
        int64_t next_el;
        std::cin >> next_el;
        elements.push(next_el);
        window.erase(window.find(elements.front()));
        window.insert(next_el);
        elements.pop();
        std::cout << *window.begin() << '\n';
    }
}

