#include <iostream>

using namespace std;

class Animal {
public :
    Animal(const string &type) : type_(type) {}

    void Eat(const string &fruit) {
        cout << type_ << " eats " << fruit << endl;
    }

    void Voice() const { // приходится делать громоздкую конструкцию,
        if (type_ == "cat") { // поскольку animal не знает про котов
            cout << "Meow!" << endl;
        } else if (type_ == "dog") {
            cout << "Whaf!" << endl;
        }
    }

private :
    const string type_;
};

class Cat : public Animal {
public :
    Cat() : Animal("cat") {}
};

class Dog : public Animal {
public :
    Dog() : Animal("dog") {}
};

void MakeSound(const Animal &a) {
    a.Voice();
}

int main() {
    Cat c;
    Dog d;
    MakeSound(c);
    MakeSound(d);
    return 0;
}