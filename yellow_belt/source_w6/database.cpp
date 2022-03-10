#include <iomanip>
#include "database.h"

constexpr char sep = '-';

void Database::Print(std::ostream &os) {
    for (auto const &el : db_) {
        auto date = el.first;
        os << date << " " << el.second.first << std::endl;
    }
}

void Database::Add(const Date &date, const std::string &event) {
    auto cnt = db_.count(date);

    if (cnt) {
        auto it_up = db_.upper_bound(date);
        auto it_low = db_.lower_bound(date);
        for (auto it = it_low; it != it_up; ++it) {
            if (it->second.first == event)
                return;
        }
    }

    db_.insert({date, {event, cnt}});
}

std::string Database::Last(Date date) {
    auto it = db_.upper_bound(date);
    if (it == db_.begin())
        throw std::invalid_argument("No entries");
    else {
        std::string s;
        int cnt;
        it = std::prev(it);
        std::tie(s, cnt) = it->second;
        std::stringstream ss;
        ss << it->first << " " << s;
        return ss.str();
    }
}

std::ostream &operator<<(std::ostream &os, const Entry &entry) {
    return os << entry.date << " " << entry.event;
}
