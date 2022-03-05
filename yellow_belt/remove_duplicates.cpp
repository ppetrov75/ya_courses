#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::endl;

template <typename T>
void RemoveDuplicates(vector<T>& v) {
    std::sort(v.begin(), v.end());
    auto it = std::unique(v.begin(), v.end());
    v.erase(it, v.end());
}

int main() {
  vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
  RemoveDuplicates(v1);
  for (int x : v1) {
    cout << x << " ";
  }
  cout << endl;

  vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
  RemoveDuplicates(v2);
  for (const string& s : v2) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}
//0 1 4 6 7
//C C++