#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <sstream>

using namespace std;

struct Date {
//    Date(int _year, int _month, int _day) : year(_year), month(_month), day(_day) {}
    int year, month, day;

    Date &operator=(const string &str) {
        istringstream is(str);
        is >> year;
        is.ignore(1);
        is >> month;
        is.ignore(1);
        is >> day;
        return *this;
    }
};

bool operator<(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

constexpr char sep = '-';

ostream &operator<<(ostream &os, const Date &date) {
    os << date.year << sep << date.month << sep << date.day;
    return os;
}

istream &operator>>(istream &is, Date &date) {
    string s;
    is >> s;
    date = s;
    return is;
}

struct Time {
//    Time(int _hours, int _minutes) : hours(_hours), minutes(_minutes) {}
    int hours, minutes;

    Time &operator=(const string &str) {
        istringstream is(str);
        is >> hours;
        is.ignore(1);
        is >> minutes;
        return *this;
    }
};

bool operator<(const Time &lhs, const Time &rhs) {
    return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
}
bool operator==(const Time &lhs, const Time &rhs) {
    return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
}

ostream & operator<<(ostream& os, const Time& t) {
    os << t.hours << ':' << t.minutes;
    return os;
}

istream &operator>>(istream &is, Time &time) {
    string s;
    is >> s;
    time = s;
    return is;
}

class AirlineTicket {
public:
//    AirlineTicket(string _from, string _to, string _airline,
//            Date dep_date, Time dep_time, Date arr_date, Time arr_time , int _price) :
//            from(_from), to(_to), airline(_airline),
//            departure_date(dep_date), departure_time(dep_time), arrival_date(arr_date), arrival_time(arr_time),
//            price(_price)
//            {}
    string from;
    string to;
    string airline;
    Date departure_date;
    Time departure_time;
    Date arrival_date;
    Time arrival_time;
    int price;
};
