#include <iostream>
#include <memory>
#include <stack>
#include <vector>

using namespace std;

// структура классов у нас остаётся той же
struct Node { // базовый класс
    virtual int Evaluate() const = 0;
};

struct Value : public Node { // класс для значения. Ранее был Digit
    Value(char digit) : _value(digit - '0') { }

    int Evaluate() const override {
        return _value;
    }

private :
    const uint8_t _value;
};

struct Variable : public Node { // класс для переменной x
    Variable(const int &x) : _x(x) {
    }

    int Evaluate() const override {
        return _x;
    }

private :
    const int &_x;
};

// алгоритм называется shunting-yard, алгоритм сортировочных станций.
struct Op : public Node { // класс для операций
    Op(char value) : precedence([value] {
        if (value == '*') {
            return 2;
        } else {
            return 1;
        }
    }()), _op(value) {
    }

    const uint8_t precedence;

    int Evaluate() const override {
        if (_op == '*') {
            return _left->Evaluate() * _right->Evaluate();
        } else if (_op == '+') {
            return _left->Evaluate() + _right->Evaluate();
        } else if (_op == '-') {
            return _left->Evaluate() - _right->Evaluate();
        }
        return 0;
    }

// передаём левый и правый операнды отдельными методами. удобнее для произвольного
    void SetLeft(shared_ptr <Node> node) {
        _left = node;
    }

    void SetRight(shared_ptr <Node> node) {
        _right = node;
    }

private :
    const char _op;
    shared_ptr<const Node> _left, _right;
};

template<class Iterator>
shared_ptr <Node> Parse(Iterator token, Iterator end, const int &x) {
// функцию Parse сделали шаблонной, т. е. для любых контейнеров из символов
    if (token == end) {
        return make_shared<Value>('0');
    }
    stack <shared_ptr<Node >> values;
    stack <shared_ptr<Op >> ops;
    auto PopOps = [&](int precedence) { // реализация алгоритма сортировочных станций
        while (!ops.empty() && ops.top()->precedence >= precedence ) {
        auto value1 = values.top();
        values.pop();
        auto value2 = values.top();
        values.pop();
        auto op = ops.top();
        ops.pop();
        op->SetRight(value1);
        op->SetLeft(value2);
        values.push(op);
    }
    };
    while (token != end) {
        const auto &value = * token;
        if (value >= '0' && value <= '9') {
            values.push(make_shared<Value>(value));
        } else if (value == 'x') {
            values.push(make_shared<Variable>(x));
        } else if (value == '*') {
            PopOps(2);
            ops.push(make_shared<Op>(value));
        } else if (value == '+' || value == '-') {
            PopOps(1);
            ops.push(make_shared<Op>(value));
        }
        ++token;
    }
    while (!ops.empty()) {
        PopOps(0);
    }
    return values.top();
}

int main() {
    string tokens;
    cout << "Enter expression : ";
    getline(cin, tokens); // считываем выражение
    int x = 0;
    auto node = Parse(tokens.begin(), tokens.end(), x);
// по итераторам начала и конца строки
    cout << "Enter x: ";
    while (cin >> x) {
        cout << " Expression value : " << node->Evaluate() << endl;
        cout << "Enter x: ";
    }
    return 0;
}