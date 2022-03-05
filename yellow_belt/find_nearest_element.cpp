#include <iostream>
#include <set>

using std::set;
using std::cout;
using std::endl;

set<int>::const_iterator
FindNearestElement(const set<int> &numbers, int border) {
    auto up_bor_it = numbers.lower_bound(border);
    if (up_bor_it == numbers.begin()) return numbers.begin();

    auto lo_bor_it = std::prev(up_bor_it);
    if (up_bor_it == numbers.end()) return lo_bor_it;

    if (border - *lo_bor_it <= *up_bor_it - border)
        return lo_bor_it;
    return up_bor_it;
}

int main() {
    set<int> numbers = {1, 4, 6};
    cout <<
         *FindNearestElement(numbers, 0) << " " <<
         *FindNearestElement(numbers, 3) << " " <<
         *FindNearestElement(numbers, 5) << " " <<
         *FindNearestElement(numbers, 6) << " " <<
         *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}
//1 4 4 6 6
//1
