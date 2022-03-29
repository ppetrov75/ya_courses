#include "../test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    const auto len = std::distance(range_begin, range_end);
    const auto step = len / 3;
    using value_t = typename RandomIt::value_type;

    if (len < 2)
        return;

    // does it work?
//    vector<value_t> v{range_begin, range_end};
    vector<value_t> v{std::make_move_iterator(range_begin), std::make_move_iterator(range_end)};
    auto third_it = v.begin() + step;
    auto third2_it = v.begin() + 2 * step;

    MergeSort(v.begin(), third_it);
    MergeSort(third_it, third2_it);
    MergeSort(third2_it, v.end());
    vector<value_t> tmp;
    std::merge(std::make_move_iterator(v.begin()), std::make_move_iterator(third_it),
               std::make_move_iterator(third_it), std::make_move_iterator(third2_it),
               std::back_inserter(tmp));

    std::merge(std::make_move_iterator(tmp.begin()), std::make_move_iterator(tmp.end()),
               std::make_move_iterator(third2_it), std::make_move_iterator(v.end()),
               range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
