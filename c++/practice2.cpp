/*A base class Pair contains a single constructor Pair(a,b) that initializes the pair with the two integer arguments a and b. A derived class sumPair inherits the base class Pair, and specializes it with a new constructor sumPair(a,b) and a new variable sum.

Both of these classes have already been defined.

Implement the new constructor sumPair(a,b), which was declared already in class sumPair. The new constructor sumPair(a,b) should initialize the inherited class Pair with integer values a,b and set the member variable "sum"  to the sum of a and b.





/* Class Pair has already been
 * declared and defined with the
 * following constructor:
 *
 *   Pair(int,int)
 *
 * that stores its two arguments in
 * two private member variables of Pair.
 *
 * Class sumPair has also already been
 * defined as follows:
 *
 * class sumPair : public Pair {
 * public:
 *   int sum;
 *   sumPair(int,int);
 * };
 * 
 * Implement the constructor
 * sumPair(int,int) such that it
 * loads the two member variables of
 * the base Pair class with its
 * arguments, and initializes the
 * member variable sum with their sum.
 



/* Below is a main() function
 * you can use to test your
 * implementation of the
 * sumPair constructor.

 
int main() {
  sumPair sp(15,16);
  std::cout << "sp(15,16).sum =" << sp.sum << std::endl;
  return 0;
}
*/

#include <iostream>
using namespace std;

class Pair {
public:
  int first, second;
  Pair(int,int);
};

Pair::Pair(int a, int b) {
  first = a;
  second = b;
}

class sumPair : public Pair {
public:
  int sum;
  sumPair(int,int);
};

sumPair::sumPair(int a, int b) : Pair(a,b) {
  sum = a + b;
}

int main(){
    sumPair sp(15,16);
    cout << "sp(15,16).sum =" << sp.sum << endl;
    return 0;
}