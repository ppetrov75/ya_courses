#include "../test_runner.h"
#include "../profile.h"

#include <map>
#include <string>
#include <future>
#include <mutex>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats &other) {
        for (auto &[k, v]: other.word_frequences) {
            word_frequences[k] += v;
        }
    }
};

Stats ExploreLine(const set<string> &key_words, string line) {
    Stats ret;

    std::istringstream is(line);
    for (string word; getline(is, word, ' ');) {
        if (key_words.count(word) != 0) {
            ret.word_frequences[word]++;
        }
    }

    return ret;
}

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input) {
    Stats result;
    for (string line; getline(input, line);) {
        result += ExploreLine(key_words, move(line));
    }
    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
    Stats result;
    vector<future<Stats>> ftrs;

    for (string line; getline(input, line);) {
        ftrs.push_back(async(ExploreLine, ref(key_words), move(line)));
    }

    for (auto &f : ftrs) {
        result += f.get();
    }
    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

//    const auto stats = ExploreKeyWords(key_words, ss);
    const auto stats = ExploreKeyWordsSingleThread(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks",  2},
            {"sucks",  1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
