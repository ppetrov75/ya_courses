#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

template<typename T>
T Sqr(T x) {
    return x * x;
}

template<typename T>
std::vector<T> Sqr(std::vector<T> v) {
    std::transform(v.begin(), v.end(), v.begin(), [](T x) { return x * x; });
    return v;
}

template<typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second>& p) {
    return { Sqr(p.first), Sqr(p.second) };
}

template<typename Key, typename Value>
std::map<Key, Value> Sqr(std::map<Key, Value> m) {
    std::transform(m.begin(), m.end(),
                   std::inserter(m, m.end()),
                   [](std::pair<const Key, Value> &p) {
                       p.second = Sqr(p.second);
                       return std::make_pair(p.first, p.second);
                   });
    return m;
}


int main() {
    std::vector<int> v = {1, 2, 3};
    std::cout << "vector:";
    for (auto x : Sqr(v)) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';

    std::map<int, int> mp = {{1, 1},
                             {2, 2},
                             {3, 3}};
    std::cout << "map:";
    for (auto m : Sqr(mp)) {
        std::cout << " {" << m.first << ", " << m.second << "} ";
    }
    std::cout << '\n';

    std::map<int, std::pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    std::cout << "map of pairs:\n";
    for (const auto &x : Sqr(map_of_pairs)) {
        std::cout << "{" << x.first << " {" << x.second.first << ' ' << x.second.second << "}}\n";
    }

}