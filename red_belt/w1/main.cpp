#include <iostream>
#include <vector>
#include <set>


template<typename Iterator>
class IteratorRange {
private :
    Iterator first, last;
public :
    IteratorRange(Iterator f, Iterator l)
            : first(f), last(l) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }
};

template<typename Container>
auto Head(Container &v, size_t top) {
    return IteratorRange{v.begin(), next(v.begin(), std::min(top, v.size()))};
}

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    IteratorRange<std::vector<int>::iterator> second_half(
            v.begin() + v.size() / 2, v.end()
    );

    for (auto x : second_half) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    const std::set<int> nums = {5, 7, 12, 8, 10, 5, 6, 1};
    for (auto x : Head(nums, 4)) {
        std::cout << x << ' ';
    }

    std::pair p(1, '5');

    return 0;
}
