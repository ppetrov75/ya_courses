#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <sstream>
#include <cassert>

#include "../profile.h"

using namespace std;

string MakeString() {
    return string(100000000, 'a');
}

vector<string> ReadStrings(istream &stream, bool use_move) {
    vector<string> strings;
    string s;
    while (stream >> s) {
        if (use_move) {
            strings.push_back(move(s));
        } else {
            strings.push_back(s);
        }
    }
    return strings;
}

string GenerateText() {
    const int SIZE = 1'000'000'000;
    const int WORD_LENGTH = 10'000'000;
    string text(SIZE, 'a');
    for (int i = WORD_LENGTH; i < SIZE; i += WORD_LENGTH) {
        text[i] = ' ';
    }
    return text;
}

string MakeString1() {
    return "C++";
}

using Id = int;

struct Object_t {
    string data;
    Id id;
    int priority{-1};
};

bool operator<(const Object_t& lhs, const Object_t & rhs) {
    return std::tie(lhs.priority, lhs.id) < std::tie(rhs.priority, rhs.id);
}

int main() {
//    {
//        LOG_DURATION("a");
//        vector<string> strings;
//         string heavy_string = MakeString();
//        strings.push_back(heavy_string);
//    }
//    {
//        LOG_DURATION("b");
//        vector<string> strings;
//        strings.push_back(MakeString());
//    }
//    {
//        LOG_DURATION("c");
//        vector<string> strings;
//        strings.push_back(std::move(MakeString()));
//    }

//    const string text = GenerateText();
//    {
//        istringstream stream(text);
//        LOG_DURATION (" without move");
//        ReadStrings(stream, false);
//    }
//    {
//        istringstream stream(text);
//        LOG_DURATION ("with move");
//        ReadStrings(stream, true);
//    }
//    {
//        istringstream stream(move(text));
//        LOG_DURATION ("with move-move");
//        ReadStrings(stream, true);
//    }

//    vector<string> strings;
//    const string s = MakeString1();
//    cout << s << "\n";
//    strings.push_back(move(s));
//    cout << s << "\n";

//    vector<int> numbers {0,1,2,3,4,5,6,7,8,9};
//    auto first = numbers.begin();
//    auto last = numbers.end();
//
//    vector<int> pool;// = move(numbers);
//    for (auto it = first; it < last; ++it) {
//        pool.push_back(move(*it));
//    }
//    // why error?
//    assert(!numbers.size());



    int cnt = 0;
    set<Object_t> objects;

    objects.insert({"aaa", cnt++, 1});
    objects.insert({"bbb", cnt++, 1});
    objects.insert({"ccc", cnt++, 0});
    cout << objects.begin()->data << endl;
    cout << prev(objects.end())->data << endl;

    return 0;
}
