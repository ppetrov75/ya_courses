#include "../test_runner.h"
#include <string>
#include <deque>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        try {
            forward_dict.at(source);
        } catch (out_of_range &) {
            //& !!!
            const auto &tref = words_storage.emplace_back(target);
            const auto &sref = words_storage.emplace_back(source);
            forward_dict[sref] = tref;
            backward_dict[tref] = sref;
        }
    }

    string_view TranslateForward(string_view source) const {
        try {
            return forward_dict.at(source);
        } catch (out_of_range &) {
            return {};
        }
    }

    string_view TranslateBackward(string_view target) const {
        try {
            return backward_dict.at(target);
        } catch (out_of_range &) {
            return {};
        }
    }

private:
    map<string_view, string_view> forward_dict;
    map<string_view, string_view> backward_dict;
    deque<string> words_storage;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
//    translator.Add("okno", "window");
    translator.Add("stol", "table");

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
