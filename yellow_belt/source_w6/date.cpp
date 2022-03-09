#include <sstream>
#include <vector>
#include <tuple>
#include <cassert>
#include <iomanip>
#include "date.h"

constexpr char sep = '-';

Date::Date(const std::string &s) {

    std::stringstream is(s);
    std::vector<int> v;

    for(std::string line; std::getline(is, line, '-'); ) {
        v.push_back(std::stoi(line));
    }
    if(v.size() != 3)
        throw std::logic_error(s + std::string (" v.size: " + v.size()));
    std::tie(y_, m_, d_) = {v[0], v[1], v[2]};
    assert(m_ > 0 && m_ <= 12 );
    assert(d_ > 0 && d_ <= 31);
}

std::string Date::to_string() const {
    std::stringstream ss;
    ss << year() << sep;
    ss << std::setw(2) << std::setfill('0') << month() << sep;
    ss << std::setw(2) << std::setfill('0') << day();
    return ss.str();
}

Date ParseDate(std::istream &is) {
    int year, month, day;
    is >> year;
    is.ignore(1);
    is >> month;
    is.ignore(1);
    is >> day;
    return {year, month, day};
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << date.to_string();
    return os;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.year(), lhs.month(), lhs.day()) < std::make_tuple(rhs.year(), rhs.month(), rhs.day());
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.year(), lhs.month(), lhs.day()) <= std::make_tuple(rhs.year(), rhs.month(), rhs.day());
}

bool operator>(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.year(), lhs.month(), lhs.day()) > std::make_tuple(rhs.year(), rhs.month(), rhs.day());
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.year(), lhs.month(), lhs.day()) >= std::make_tuple(rhs.year(), rhs.month(), rhs.day());
}

bool operator==(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.year(), lhs.month(), lhs.day()) == std::make_tuple(rhs.year(), rhs.month(), rhs.day());
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return std::make_tuple(lhs.year(), lhs.month(), lhs.day()) != std::make_tuple(rhs.year(), rhs.month(), rhs.day());
}
