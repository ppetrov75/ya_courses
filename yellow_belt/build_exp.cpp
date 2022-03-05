#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main() {

    int num;
    cin >> num;
    int cnt_op;
    cin >> cnt_op;

    string s;
    s = std::to_string(num);

    for(int i = 0; i < cnt_op; ++i) {
        char type_op;
        int arg_op;
        cin >> type_op; cin >> arg_op;

        s = "(" + s + ") " + type_op + " " + std::to_string(arg_op);
    }

    cout << s;
}
//1
//2
//+ 3
//- 4
//((1) + 3) - 4