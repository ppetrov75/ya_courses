#include <iostream>
#include <cassert> // подключаем assert'ы

using namespace std;

int Sum(int x, int y) {
    return x + y;
}

void TestSum() { // собираем набор тестов для функции Sum
    assert (Sum(2, 3) == 5); // мы ожидаем, что 2+3=5
    assert (Sum(-2, -3) == -5); // проверка отрицательных чисел
    assert (Sum(-2, 0) == -2); // проверка прибавления 0
    assert (Sum(-2, 2) == 0); // проверка, когда сумма = 0
    cout << " TestSum OK" << endl;
}

int main() {
    TestSum();
    return 0;
}