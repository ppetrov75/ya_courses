#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    auto len = range_end - range_begin;
    if (len < 2) return;

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto b = elements.begin();
    auto e = elements.end();
    auto mid = b + len / 2;
    MergeSort(b, mid);
    MergeSort(mid, e);

    std::merge(b, mid, mid, e, range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}