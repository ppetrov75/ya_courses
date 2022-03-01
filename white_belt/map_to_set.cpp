#include <iostream>
#include <map>
#include <set>
#include <algorithm>

int main() {

    std::map<int, std::string> m{
            {1, "odd"},
            {2, "even"},
            {3, "odd"},
            {4, "even"},
            {5, "odd"}};

    std::set<std::string> s;
    std::transform(m.begin(), m.end(), std::inserter(s, s.begin()), [](auto &kv) { return kv.second; });

    for (const auto &i : s) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    s.clear();
    for (const auto &mc : m) {
        s.insert(mc.second);
    }

    for (const auto &i : s) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}
