#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>

using namespace std;

map<string_view, string_view> dict;
deque<string> storage;

void add_words(string_view src, string_view trgt) {
    try {
        auto it = dict.find(src);
        if (it == dict.end()) {
            string t{trgt};
            auto& ref = storage.emplace_back(t);
            cout << trgt << ":" << &ref << endl;
            dict[src] = ref;

            auto & ref2 = storage.emplace_back(string(src));
            cout << src << ":" << &ref2 << endl;
            dict[trgt] = ref2;
        }
    } catch (out_of_range &) {

    }

}

string_view get_translate(string_view src) {
    try {
        return dict.at(src);
    } catch (out_of_range &) {
        return "";
    }
}

template<typename T>
class Airport {
public:
    Airport() {
//        cout << sizeof(T) << endl;
        cout << (int)T::Last_ << endl;

    }

};

int main() {

//    add_words("odin", "one");
//    add_words("dva", "two");
//
//    cout << get_translate("odin") << endl;
//    cout << get_translate("one") << endl;
//    cout << get_translate("dva") << endl;
//    cout << get_translate("two") << endl;

    enum class MoscowAirport {
        VKO,
        SVO,
        DME,
        ZIA,
        Last_
    };

    Airport<MoscowAirport> a;

    enum class SmallCountryAirports {
        Airport_1,
        Airport_2,
        Airport_3,
        Airport_4,
        Airport_5,
        Airport_6,
        Airport_7,
        Airport_8,
        Airport_9,
        Airport_10,
        Airport_11,
        Airport_12,
        Airport_13,
        Airport_14,
        Airport_15,
        Last_
    };
    Airport<SmallCountryAirports> b;
}
