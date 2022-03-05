#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;


int main() {
    int n;
    cin >> n;

    vector<char> v(n);
    std::iota(v.begin(), v.end(), '1');
    std::reverse(v.begin(), v.end());

    std::string s(v.begin(), v.end());
    do {
        std::copy(s.begin(), s.end(), std::ostream_iterator<char>(cout, " "));
        cout << endl;
    }
    while(std::prev_permutation(s.begin(), s.end()));
}

//3
//3 2 1
//3 1 2
//2 3 1
//2 1 3
//1 3 2
//1 2 3