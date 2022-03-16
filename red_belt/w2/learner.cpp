#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string> &words) {
        int newWords = 0;
        for (const auto &word : words) {
            if (dict.find(word) == dict.end()) {
                dict.insert(word);
                ++newWords;
            }
        }
        return newWords;
    }

    vector<string> KnownWords() {
        return {dict.begin(), dict.end()};
    }
};

int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}
// set
//time ../cmake-build-debug/red_belt<../steven_prata_cpp_eng.txt > out.txt
//
//real	0m0,722s
//user	0m0,602s
//sys	0m0,120s
//time ../cmake-build-debug/red_belt<../steven_prata_cpp_eng.txt > /dev/null
//
//real	0m0,562s
//user	0m0,534s
//sys	0m0,028s
//
// vector
//time ../cmake-build-debug/red_belt<../steven_prata_cpp_eng.txt > out.txt
//
//real	0m30,236s
//user	0m30,092s
//sys	0m0,144s
//
//time ../cmake-build-debug/red_belt<../steven_prata_cpp_eng.txt > /dev/null
//
//real	0m31,113s
//user	0m31,052s
//sys	0m0,040s




