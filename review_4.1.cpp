#include <algorithm>
#include <vector>
#include <iostream>

using i64 = int64_t;

i64 closest(const std::vector<i64>& nums, i64 target) {
    auto low = std::lower_bound(nums.begin(), nums.end(), target);
    if (low != nums.end() && low != nums.begin()) {
        auto m = (std::abs(target - *low) < std::abs(target - *prev(low))) ? *low : *prev(low);
        return m;
    } else if (low != nums.end()) {
        return *low;
    } else {
        return *prev(nums.end());
    }
}

int main() {
    size_t firstSize, secSize;
    std::cin >> firstSize >> secSize;
    std::vector<i64> closestNumbers(firstSize);
    std::vector<i64> numbers(secSize);
    
    for (i64& n : closNumbers) {
        std::cin >> n;
    }
    for (i64& n : numbers) {
        std::cin >> n;
    }

    for (i64 number : numbers) {
        std::cout << closest(closNumbers, number) << '\n';
    }
}

