#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

template<typename K, typename V>
V &GetRefStrict(std::map<K, V> &m, K key) {
    try {
        return m.at(key);
    }
    catch (std::out_of_range) {
        throw std::runtime_error("error");
    }
}

int main() {
    std::map<int, std::string> m = {{0, "value"}};
    auto &item = GetRefStrict(m, 0);
    item = "newvalue";
    std::cout << m[0] << '\n'; // выведет newvalue
}