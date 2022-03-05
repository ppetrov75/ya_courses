#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    auto len = range_end - range_begin;
    if (len <= 1) return;

    using v_type = vector<typename RandomIt::value_type>;
    v_type elements(range_begin, range_end);

    auto b = elements.begin();
    auto e = elements.end();
    auto mid = b + len / 3;
    auto mid1 = mid + len / 3;
    MergeSort(b, mid);
    MergeSort(mid, mid1);
    MergeSort(mid1, e);

    v_type tmp;

    std::merge(b, mid, mid, mid1, std::back_inserter(tmp));
    std::merge(tmp.begin(), tmp.end(), mid1, e, range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
//0 1 4 4 4 5 6 6 7