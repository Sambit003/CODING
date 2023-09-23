/*
Assignment:
Write a C++ program for Quick Sort with the following features:
1. It must for genaric data type. Use the concept of Template.
2. Use the concept of Dynamic Memory Allocation to take inputs.
3. Inputs must be accepted using Overloaded  >>  operator.
4. Content before and after sorting must be displayed using overloaded  <<  operator.
*/

#include <iostream>
#include <unordered_map>
using namespace std;

template <class T> class QuickSort {
    T *arr=NULL;
    int size;
    void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }

    int partition(int low, int high) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    void quick_sort(T *arr, int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quick_sort(arr, low, pi - 1);
            quick_sort(arr, pi + 1, high);
        }
    }

public:
    //constructor
    QuickSort() {
        cout << "Enter size of array: ";
        cin >> size;
        arr = new T[size]; //dynamic memory allocation
        if (arr == NULL) {
            cout << "Memory not allocated." << endl;
            exit(0);
        } else {
            cout << "Array of size " << size << " created.\n";
        }
    }
    void sort() {
        quick_sort(arr, 0, size - 1);
    }

    //overload >> operator
    friend istream &operator>>(istream &input, QuickSort &q) {
        for (int i = 0; i < q.size; i++)
            input >> q.arr[i];
        return input;
    }

    //overload << operator
    friend ostream &operator<<(ostream &output, QuickSort &q) {
        for (int i = 0; i < q.size; i++)
            output << q.arr[i] << " ";
        return output;
    }

    //destructor
    ~QuickSort() {
        delete[] arr; arr = NULL;
        cout << "Array of size " << size << " deleted." << endl;
    }
};

// string switch case enabled for choice
unordered_map<string, int> choice_map = {
    {"int", 1},
    {"integer", 1},
    {"float", 2},
    {"double", 3},
    {"character", 4},
    {"char", 4},
    {"string", 5}
};

int main() {
    string choice;
    cout << "Enter data type of array: ";
    cin >> choice;
    // Dynamic instantiation of class
    switch (choice_map[choice]) {
        case 1: {
            QuickSort<int> q;
            cout << "Enter elements of array: ";
            cin >> q;
            cout << "Before sorting: " << q << endl;
            q.sort();
            cout << "After sorting: " << q << endl;
            break;
        }
        case 2: {
            QuickSort<float> q;
            cout << "Enter elements of array: ";
            cin >> q;
            cout << "Before sorting: " << q << endl;
            q.sort();
            cout << "After sorting: " << q << endl;
            break;
        }
        case 3: {
            QuickSort<double> q;
            cout << "Enter elements of array: ";
            cin >> q;
            cout << "Before sorting: " << q << endl;
            q.sort();
            cout << "After sorting: " << q << endl;
            break;
        }
        case 4: {
            QuickSort<char> q;
            cout << "Enter elements of array: ";
            cin >> q;
            cout << "Before sorting: " << q << endl;
            q.sort();
            cout << "After sorting: " << q << endl;
            break;
        }
        case 5: {
            QuickSort<string> q;
            cout << "Enter elements of array: ";
            cin >> q;
            cout << "Before sorting: " << q << endl;
            q.sort();
            cout << "After sorting: " << q << endl;
            break;
        }
        default: {
            cout << "Invalid choice." << endl;
            exit(0);
        }
    }

    return 0;
}