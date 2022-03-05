#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <ctime>
#include <cassert>
#include <chrono>

using std::vector;
using std::cout;
using std::endl;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    auto len = range_end - range_begin;
    if (len <= 1) return;

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto b = elements.begin();
    auto e = elements.end();
    auto mid = b + len / 2;
    MergeSort(b, mid);
    MergeSort(mid, e);

    std::merge(b, mid, mid, e, range_begin);
}

template<typename RandomIt>
void MergeSort3(RandomIt range_begin, RandomIt range_end) {
    auto len = range_end - range_begin;
    if (len <= 1) return;

    using v_type = vector<typename RandomIt::value_type>;
    v_type elements(range_begin, range_end);

    auto b = elements.begin();
    auto e = elements.end();
    auto mid = b + len / 3;
    auto mid1 = mid + len / 3;
    MergeSort3(b, mid);
    MergeSort3(mid, mid1);
    MergeSort3(mid1, e);

    v_type tmp;

    std::merge(b, mid, mid, mid1, std::back_inserter(tmp));
    std::merge(tmp.begin(), tmp.end(), mid1, e, range_begin);
}

std::vector<int> generate_random_values(int max_value = 1, int min_value = 0, int range = 1) {

    std::vector<int> v;
    v.resize(range);

    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine gen(r());
    std::uniform_int_distribution<int> dist(min_value, max_value);
    auto rand = std::bind(dist, std::ref(gen));

    std::generate(v.begin(), v.end(), rand);

    return v;
}

int main() {

    auto clock_in_sec = [](double t) { return t * 1000.0 / CLOCKS_PER_SEC; };

    {
        int range;
        range = std::pow(2, 20);
        vector<int> t;
        assert(range < t.max_size());

        vector<int> v(range);
        v = generate_random_values(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), range);
        auto v2 = v;

        auto start = std::chrono::system_clock::now();
        MergeSort(v.begin(), v.end());
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();

        start = std::chrono::system_clock::now();
        std::sort(v2.begin(), v2.end());
        auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();

        cout << t1 << " ms,   " << t2 << " ms\n";
    }

    // /3 part
    {
        int range;
        range = std::pow(3, 13);
        vector<int> t;
        assert(range < t.max_size());

        vector<int> v(range);
        v = generate_random_values(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), range);
        auto v2 = v;

        auto start = std::chrono::system_clock::now();
        MergeSort3(v.begin(), v.end());
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();

        start = std::chrono::system_clock::now();
        std::sort(v2.begin(), v2.end());
        auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();

        cout << t1 << " ms,   " << t2 << " ms\n";
    }
    return 0;
}
//  844 ms,   380 ms
// 1769 ms,   593 ms
