#ifndef YELLOW_BELT_DATE_H
#define YELLOW_BELT_DATE_H

#include <string>
#include <iostream>

class Date {
private:
    int y_{0};
    int m_{13};
    int d_{32};

public:

    Date(int y, int m, int d) : y_(y), m_(m), d_(d) {}

    Date(const std::string &s);

    int year() const { return y_; }

    int month() const { return m_; }

    int day() const { return d_; }

    std::string to_string() const;
};

bool operator<(const Date &lhs, const Date &rhs);

bool operator<=(const Date &lhs, const Date &rhs);

bool operator>(const Date &lhs, const Date &rhs);

bool operator>=(const Date &lhs, const Date &rhs);

bool operator==(const Date &lhs, const Date &rhs);

bool operator!=(const Date &lhs, const Date &rhs);

Date ParseDate(std::istream &is);

std::ostream &operator<<(std::ostream &, const Date &date);

#endif //YELLOW_BELT_DATE_H
