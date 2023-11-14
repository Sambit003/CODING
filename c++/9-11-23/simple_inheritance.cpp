// WAP in C++ which will satisfy the definition of simple inheritance

#include<iostream>
using namespace std;

class account{
    public:
    float salary = 50000;
};

class programmer: public account{
    public:
    float bonus = 5000;
};

int main(){
    programmer p1;
    cout << "\tSalary: " << p1.salary << endl;
    cout << "\tBonus: " << p1.bonus << endl;
    return 0;
}