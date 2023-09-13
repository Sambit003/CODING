#include <iostream>
using namespace std;

class outside {
    int x;
    public:
    class inside {
        public:
        int x;
        static int y;
        void func(){
            cout << "\tValue of static var Y of class inside: " << inside::y << endl;
        }
    };
};

int outside::inside::y = 20;

int main() {
    outside::inside i;
    i.func();
    return 0;
}