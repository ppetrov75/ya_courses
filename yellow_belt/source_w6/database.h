#ifndef YELLOW_BELT_DATABASE_H
#define YELLOW_BELT_DATABASE_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

#include "date.h"
#include "event.h"

struct Entry {
    Date date;
    std::string event;
};

std::ostream &operator<<(std::ostream &os, const Entry &entry);

class Database {

public:
    void Add(const Date& date, const std::string &event);

    void Print(std::ostream &os);

    std::string Last(Date date);

    template<class Predicate> std::vector<Entry> FindIf(Predicate pred) const {
        std::vector<Entry> ret;
        for(const auto& d : db_) {
            if (pred(d.first, d.second.first)){
                ret.push_back({d.first, d.second.first});
            }
        }
        return ret;
    }

    template<class Predicate> int RemoveIf(Predicate pred) {
        int cnt = 0;
        for(auto it = db_.begin(); it != db_.end();) {
            if(pred(it->first, it->second.first)){
                it = db_.erase(it);
                ++cnt;
            }
            else
                ++it;
        }

        return cnt;
    }

private:
    // date - event - counter
    std::multimap<Date, std::pair<std::string, int>> db_;
};

#endif //YELLOW_BELT_DATABASE_H
