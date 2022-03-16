#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// TODO
class ReadingManager
{
public:
    ReadingManager() :
            // -1 --> -INDENTIFICATOR?
            people(MAX_USER_COUNT_ + 1, -1),
            pages(MAX_PAGE_COUNT_ + 1, 0) {}

    void Read(int user_id, int page_count)
    {
        // Inverse -INDENTIFICATOR ?
        for (int i = people[user_id] + 1; i <= page_count; i++)
        {
            ++pages[i];
        }
        people[user_id] = page_count;
    }

    double Cheer(int user_id) const
    {
        // -INDENTIFICATOR ?
        if (people[user_id] == -1)
        {
            return 0;
        }

        if (pages[0] == 1)
        {
            return 1;
        }
        return static_cast<double>(pages[0] - pages[people[user_id]]) / static_cast<double>(pages[0] - 1);
    }
private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    std::vector<int> people;
    std::vector<int> pages;
};
/*
class ReadingManager {
public:
    ReadingManager()
            : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
              sorted_users_(),
              user_positions_(MAX_USER_COUNT_ + 1, -1) {}

    void Read(int user_id, int page_count) {
        if (user_page_counts_[user_id] == 0) {
            AddUser(user_id);
        }
        user_page_counts_[user_id] = page_count;
        int &position = user_positions_[user_id];
        while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
            SwapUsers(position, position - 1);
        }
    }

    double Cheer(int user_id) const {
        if (user_page_counts_[user_id] == 0) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        const int page_count = user_page_counts_[user_id];
        int position = user_positions_[user_id];
        while (position < user_count &&
               user_page_counts_[sorted_users_[position]] == page_count) {
            ++position;
        }
        if (position == user_count) {
            return 0;
        }
        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Простой способ сделать это — умножить его на 1.0.
        return (user_count - position) * 1.0 / (user_count - 1);
    }

private:
    // Статическое поле не принадлежит какому-то конкретному
    // объекту класса. По сути это глобальная переменная,
    // в данном случае константная.
    // Будь она публичной, к ней можно было бы обратиться снаружи
    // следующим образом: ReadingManager::MAX_USER_COUNT.
    static const int MAX_USER_COUNT_ = 100'000;

    vector<int> user_page_counts_;
    vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
    vector<int> user_positions_; // позиции в векторе sorted_users_

    int GetUserCount() const {
        return sorted_users_.size();
    }

    void AddUser(int user_id) {
        sorted_users_.push_back(user_id);
        user_positions_[user_id] = sorted_users_.size() - 1;
    }

    void SwapUsers(int lhs_position, int rhs_position) {
        const int lhs_id = sorted_users_[lhs_position];
        const int rhs_id = sorted_users_[rhs_position];
        swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
        swap(user_positions_[lhs_id], user_positions_[rhs_id]);
    }
};
*/

int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}