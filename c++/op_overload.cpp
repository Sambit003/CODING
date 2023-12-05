#include <iostream>
using namespace std;

class addbyten {
    int a;
public:
  addbyten(int x = 0) {
    a = x;
  }

  addbyten operator+(const addbyten& obj){
    addbyten result;
    result.a = obj.a + 10;
    return result;
  }

  int get_a() {
    return a;
  }
};

int main() {
  addbyten obj(15);
  addbyten res = obj + 10;
  cout << "Result is: " << res.get_a() << endl;
  return 0;
}
