// WAP in C++ to implement virtual function.

#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing a circle" << endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing a square" << endl;
    }
};

int main() {
    Shape* shapes[] = {new Circle(), new Square()};

    for (Shape* shape : shapes) {
        shape->draw();
    }

    return 0;
}
