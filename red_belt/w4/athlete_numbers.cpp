#include <iostream>
#include <list>
#include <vector>

using namespace std;

const int MAX_ATHLETES = 100'000;

int main() {

    list<int> athlete_numbers_list;
    vector<list<int>::iterator> athlete_positions(MAX_ATHLETES+1, athlete_numbers_list.end());

    int query_numbers;
    cin >> query_numbers;

    for (int i = 0; i < query_numbers; ++i) {
        int athlete_num, athlete_before_num;
        cin >> athlete_num >> athlete_before_num;

        athlete_positions[athlete_num] = athlete_numbers_list.insert(athlete_positions[athlete_before_num], athlete_num);
    }

    for(auto x : athlete_numbers_list) {
        cout << x << '\n';
    }

    return 0;
}

//5
//42 0
//17 42
//13 0
//123 42
//5 13
//
//17
//123
//42
//5
//13