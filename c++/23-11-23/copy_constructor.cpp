// WAP in C++ to implement the conecpt of copy constructor.

#include <iostream>
using namespace std;

class Point {
public:
  int x, y;

  Point(int x = 0, int y = 0) {
    this->x = x;
    this->y = y;
  }

  Point(const Point& obj) {  // Copy constructor
    x = obj.x;
    y = obj.y;
  }

  void display() {
    cout << "x = " << x << ", y = " << y << endl;
  }
};

int main() {
  Point p1(10, 20);
  Point p2 = p1;  // Copy constructor is called here

  p1.display();
  p2.display();

  return 0;
}
