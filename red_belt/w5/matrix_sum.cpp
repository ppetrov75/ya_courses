#include <vector>
#include <future>
#include <execution>

#include "../test_runner.h"
#include "../profile.h"


using namespace std;

template<typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors &result, size_t first_row, size_t column_size) {
    for_each(
            execution::par,
            begin(result), end(result), [& first_row, column_size](vector<int> &row) {
                row.reserve(column_size);
                for (size_t column = 0; column < column_size; ++column) {
                    row.push_back(first_row ^ column);
                }
                ++first_row;
            }
    );
}

vector<vector<int >> GenerateSingleThread(size_t size) {
    vector<vector<int >> result(size);
    GenerateSingleThread(result, 0, size);
    return result;
}

using Container_t = vector<vector<int>>;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    int64_t ret = 0;
    for(const auto& c : matrix) {
        for(const auto& r : c) {
            ret += r;
        }
    }
    return ret;
}

int64_t CalculateMatrixSum(Container_t::const_iterator begin, Container_t::const_iterator end) {
    int64_t ret = 0;
    for(auto it = begin; it != end; ++it) {
        for(auto it1 = it->begin(); it1 != it->end(); ++it1) {
            ret += *it1;
        }
    }
    return ret;
}
//template <typename ContainerOfVectors>
//int64_t SumSingleThread(const ContainerOfVectors& matrix) {
//    int64_t sum = 0;
//    for (const auto& row : matrix) {
//        for (auto item : row) {
//            sum += item;
//        }
//    }
//    return sum;

//}

int64_t CalculateMatrixSumMulti(const Container_t &matrix) {
    int64_t ret = 0;
    const int num_proc = 8;
    auto matrix_size = matrix.size();
    auto page_size = matrix_size/num_proc;
    vector<pair<Container_t::const_iterator, Container_t::const_iterator>> pages;

    auto matrix_end_it = matrix.end();
    for(auto it = matrix.begin(); it != matrix_end_it;) {
        auto shift_len = min(page_size, (size_t)distance(it, matrix_end_it));
        auto page_begin = it;
        advance(it, shift_len);
        pages.push_back(make_pair(page_begin, it));
    }

    vector<future<int64_t>> ftrs;
    for(auto & page : pages) {
        // 1sec 200ms
//        ret += CalculateMatrixSum(page.first, page.second);
        // 800ms
//        ret += CalculateMatrixSum({page.first, page.second});
        // 230ms
        ftrs.push_back(async([&page]{return CalculateMatrixSum({page.first, page.second});}));
        // single thread 680ms

    }
    for(auto& f : ftrs) {
        ret += f.get();
    }

    return ret;
}

int64_t CalculateMatrixSumParExec(const vector<vector<int>> &matrix) {
    int64_t ret = 0;
    for_each(
            execution::par,
            begin(matrix), end(matrix), [&ret](const vector<int> &row) {
                for (const auto& r : row) {
                    ret += r;
                }
            }
    );

    return ret;
}

//*****
template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
            : first(begin)
            , last(end)
            , size_(distance(first, last))
    {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator {
private:
    vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (size_t left = distance(begin, end); left > 0; ) {
            size_t current_page_size = min(page_size, left);
            Iterator current_page_end = next(begin, current_page_size);
            pages.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
    int64_t sum = 0;
    for (const auto& row : matrix) {
        for (auto item : row) {
            sum += item;
        }
    }
    return sum;
}

int64_t CalculateMatrixSumExample(const vector<vector<int>>& matrix) {
    vector<future<int64_t>> futures;
    for (auto page : Paginate(matrix, 2000)) {
        futures.push_back(async([=] { return SumSingleThread(page); }));
    }
    int64_t result = 0;
    for (auto& f : futures) {
        result += f.get();
    }
    return result;
}
//*****

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9,  10, 11, 12},
            {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}
const size_t MATRIX_SIZE = 9000;

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);

    auto test_vec = GenerateSingleThread(MATRIX_SIZE);
    {
        LOG_DURATION("single thread calc")
        cout << CalculateMatrixSum(test_vec) << endl;
    }
    {
        LOG_DURATION("multi thread calc")
        cout << CalculateMatrixSumMulti(test_vec) << endl;
    }
    {
        LOG_DURATION("multi thread calc from Example")
        cout << CalculateMatrixSumExample(test_vec) << endl;
    }
    {
        LOG_DURATION("execution parallel thread calc")
        cout << CalculateMatrixSumParExec(test_vec) << endl;
    }

}

// 1sec 200ms
//        ret += CalculateMatrixSum(page.first, page.second);
// 800ms
//        ret += CalculateMatrixSum({page.first, page.second});
// 230ms
//ftrs.push_back(async([&page]{return CalculateMatrixSum({page.first, page.second});}));
// single thread 680ms
// example 211ms