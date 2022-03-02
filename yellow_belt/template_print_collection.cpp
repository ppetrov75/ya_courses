#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>

using namespace std;

template<typename First, typename Second>
// для pair
ostream &operator<<(ostream &out, const pair<First, Second> &p) {
    return out << " pair: [" << p.first << ',' << p.second << ']'; // тоже изменили
}

template<typename Collection>
// тип коллекции
string Join(const Collection &c, char d) { // передаем коллекцию и разделитель
    stringstream ss; // завели строковый поток
    bool first = true; // первый ли это элемент?
    for (const auto &i : c) {
        if (!first) {
            ss << d; // если вывели не первый элемент - кладем поток в разделитель
        }
        first = false; // т.к. следующий элемент точно не будет первым

        ss << i; // кладем следующий элемент в поток
    }
    return ss.str();
}

template<typename T>
// для vector изменили код и добавили скобочки
ostream &operator<<(ostream &out, const vector<T> &vi) {
    return out << "vector: (" << Join(vi, ',') << ')';
} // оператор вывода возвращает ссылку на поток
template<typename Key, typename Value>
// для map убрали аналогично vector
ostream &operator<<(ostream &out, const map<Key, Value> &m) {
    return out << "map: {" << Join(m, ',') << '}'; // и добавили фигурные скобочки
}

int main() {
    vector<double> vi = {1.4, 2, 3};
    pair<int, int> m1 = {1, 2};
    map<double, double> m2 = {{1.4, 2.1},
                              {3.4, 4}};
    cout << vi << '\n' << m1 << '\n' << m2 << endl;

    vector<vector<int >> vv = {{1, 2},
                               {3, 4}};
    cout << vv << endl;

}
// [1.4, 2,3] (1, 2) {(1.4, 2.1), (3.4, 4)}