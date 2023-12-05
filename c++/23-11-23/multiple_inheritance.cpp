// WAP in C++ to demonstrate multiple inheritance.

#include <iostream>
using namespace std;

class Shape {
public:
  virtual void draw() = 0;
};

class Colorable {
public:
  virtual void setColor(const string& color) = 0;
  virtual string getColor() const = 0;
};

class Circle : public Shape, public Colorable {
private:
  double radius;
  string color;

public:
  Circle(double radius) : radius(radius) {} 

  void draw() override {
    cout << "Drawing a circle with radius " << radius << endl;
  }

  void setColor(const string& color) override {
    this->color = color;
  }

  string getColor() const override {
    return color;
  }
};

int main() {
  Circle circle(5.0);
  circle.setColor("red");
  circle.draw();

  cout << "Circle color: " << circle.getColor() << endl;

  return 0;
}
