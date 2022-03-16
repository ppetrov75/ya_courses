#include "../test_runner.h"

using namespace std;

template<typename T>
class Table {
    size_t row_;
    size_t column_;
    std::vector<std::vector<T>> table_;
public:
    Table(size_t row, size_t column)  {
        Resize(row, column);
    }
    std::pair<size_t, size_t> Size() {
        return {row_, column_};
    }
    void Resize(size_t new_row, size_t new_column) {
        row_ = new_row;
        column_ = new_column;
        table_.resize(row_);
        for(auto & clmn : table_) {
            clmn.resize(column_);
        }
    }

    std::vector<T>& operator[](int row){
        return table_[row];
    };
    const std::vector<T>& operator[](int row) const{
        return table_[row];
    };
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
