#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <iterator>


using namespace std;
using namespace chrono;


#define MERGE(id) var_##id
#define MAKE_LABEL(id) MERGE(id)
#define UNIQ_ID MAKE_LABEL(__COUNTER__)

class AddDuration;

#define ADD_DURATION(value) \
AddDuration UNIQ_ID{value};


void LeftStrip(string_view &sv) {
    while (!sv.empty() && isspace(sv[0])) {
        sv.remove_prefix(1);
    }
}

string_view ReadToken(string_view &sv) {
    LeftStrip(sv);

    auto pos = sv.find(' ');
    auto result = sv.substr(0, pos);
    // "+ 1" remove (found) next space
    sv.remove_prefix(pos != sv.npos ? pos + 1 : sv.size());
    return result;
}

vector<string_view> SplitIntoWordsView(string_view str) {
    vector<string_view> result;

    for (string_view word = ReadToken(str); !word.empty(); word = ReadToken(str)) {
        result.push_back(word);
    }

    return result;
}

struct TotalDuration {
    string message;
    steady_clock::duration value;

    explicit TotalDuration(const string &msg = "")
            : message(msg + ": "), value(0) {
    }

    ~TotalDuration() {
        ostringstream os;
        os << message
           << duration_cast<milliseconds>(value).count()
           << " ms" << endl;
        cerr << os.str();
    }
};

class AddDuration {
public:
    explicit AddDuration(steady_clock::duration &dest)
            : add_to(dest), start(steady_clock::now()) {
    }

    explicit AddDuration(TotalDuration &dest)
            : AddDuration(dest.value) {
    }

    ~AddDuration() {
        add_to += steady_clock::now() - start;
    }

private:
    steady_clock::duration &add_to;
    steady_clock::time_point start;
};


istream &ReadLine(istream &input, string &s, TotalDuration &dest) {
    ADD_DURATION(dest);
    return getline(input, s);
}

int main() {
    TotalDuration read("Total read");
    TotalDuration parse("Total parse");
    for (string line; ReadLine(cin, line, read);) {
        ADD_DURATION(parse);
        const auto words = SplitIntoWordsView(line);
        for (auto &w : words) {
            cout << "'" << w << "' ";
        }
    }
}
