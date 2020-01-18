#include <iostream>

int digitS(int a) {
    int s = 0;
    while (a > 0) {
        s += a % 10;
        a /= 10;
    }
    return s;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << digitS(n);
    return 0;
}

