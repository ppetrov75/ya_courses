#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;

vector <string> SplitIntoWords(const string &s) {
    vector <string> v;

    auto end = s.end();
    auto sep = ' ';
    // check end for empty string
    for(auto it = s.begin(); it != end; ++it) {
        auto b = it;
        it = std::find(b, end, sep);

        auto s = std::string(b, it);
        if(s.length()) v.push_back(s);

        if (it == end) break;
    }

    return v;
}

int main() {
    string s = " C  Cpp Java   Python ";
    vector <string> words = SplitIntoWords(s);
    std::cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            std::cout << "/";
        }
        std::cout << "'" << *it << "'";
    }
    std::cout << std::endl;

    return 0;
}
//4 'C'/'Cpp'/'Java'/'Python'