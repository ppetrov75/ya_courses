#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

template<typename It>
// написали шаблонную функцию
void PrintRange(It range_begin, // поменяли здесь на шаблон итератора
                It range_end) { // и тут
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    vector <string > langs = {" Python ", "C++", "C", "Java", "C#"};
    vector <string > c_langs ( langs .size ()); // вектор, куда мы копируем, должен быть
// объявлен и иметь подходящий размер
    auto it = copy_if ( begin ( langs ), end( langs ), begin ( c_langs ),
                        []( const string & lang) {
                            return lang [0] == 'C';
                        });
    PrintRange (begin ( c_langs ), end( c_langs ));

    return 0;
}
