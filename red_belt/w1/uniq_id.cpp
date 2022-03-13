#include <string>
#include <vector>
using namespace std;

#define MERGE(id) var_##id
#define MAKE_LABEL(id) MERGE(id)
#define UNIQ_ID MAKE_LABEL(__COUNTER__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
  int UNIQ_ID = 5; string UNIQ_ID = "hello";
}