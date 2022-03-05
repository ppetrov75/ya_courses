#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

void PrintVectorPart(const vector<int>& v) {

    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x < 0;});
    auto cnt = 0;
    while (it != v.begin()) {
        --it;
        std::cout << *it << ' ';
        ++cnt;
    }
    if (cnt) std::cout << std::endl;
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    PrintVectorPart({6, 1, 8, 5, 4});
    return 0;
}