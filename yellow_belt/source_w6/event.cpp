#include <iostream>
#include <iterator>
#include "event.h"

Event::Event(const std::string &evt) : event_(evt) {}

std::string ParseEvent(std::istream &is) {
    std::string s;
    std::getline(is, s);
    auto st = s.find_first_not_of(' ');
    auto end = s.find_last_not_of(' ');
    return s.substr(st, end - st + 1);;
}

