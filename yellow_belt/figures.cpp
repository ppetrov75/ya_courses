#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;

    virtual double Perimeter() const = 0;

    virtual double Area() const = 0;
};

class Rect : public Figure {
public:
    Rect(int width, int height) : width_(width), height_(height) {}

    string Name() const override {
        return "RECT";
    }

    double Perimeter() const override {
        return (width_ + height_) * 2;
    }

    double Area() const override {
        return width_ * height_;
    }

    const int width_;
    const int height_;
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c) : a_(a), b_(b), c_(c) {}

    string Name() const override {
        return "TRIANGLE";
    }

    double Perimeter() const override {
        return a_ + b_ + c_;
    }

    double Area() const override {
        // Heron formula
        auto p = Perimeter() / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

    const int a_;
    const int b_;
    const int c_;
};

class Circle : public Figure {
public:
    explicit Circle(int radius) : radius_(radius) {}

    string Name() const override {
        return "CIRCLE";
    }

    double Perimeter() const override {
        return 2 * M_PI * radius_;
    }

    double Area() const override {
        return M_PI * radius_ * radius_;
    }

    const int radius_;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string cmd;
    is >> cmd;

    if (cmd == "RECT") {
        int w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    } else if (cmd == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if (cmd == "CIRCLE") {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    }

    throw runtime_error("bad command");
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);
        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
