#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

template<typename T>
std::vector<T> FindGreaterElements(const std::set<T> &s, const T &border) {
    std::vector<T> v;
//    auto it = std::find_if(s.begin(), s.end(), [border](const T& x){ return x > border;});
    auto it = std::find(s.begin(), s.end(), border);
    if (it != s.end())
        std::copy(std::next(it), s.end(), std::back_inserter(v));
    return v;
}

int main() {
    for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::string to_find = "Python";
    std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
    return 0;
}