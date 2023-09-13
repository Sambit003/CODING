/*
Write a C++ program for Matrix Addition and Matrix 
Multiplication by overloading + and * operators. 
You have to use >>  operator to input a matrix and << operator to display a matrix.
Overload the input and output operators. Input operator should be able to take input
in the following format: 
1 2 3
4 5 6
7 8 9
where each row is separated by a new line and each element in a row is separated by a space.
Output operator should display matrix in
the following format:
1 2 3
4 5 6
7 8 9
*/

#include <iostream>
using namespace std;

class Matrix {
    int **mat;
    int row, col;

public:
    Matrix(int r, int c) {
        row = r;
        col = c;
        mat = new int *[row];
        for (int i = 0; i < row; i++)   mat[i] = new int[col];
    }

    Matrix operator+(Matrix m) {
        Matrix temp(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++)   temp.mat[i][j] = mat[i][j] + m.mat[i][j];
        }
        return temp;
    }

    Matrix operator*(Matrix m) {
        Matrix temp(row, m.col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                temp.mat[i][j] = 0;
                for (int k = 0; k < col; k++)   temp.mat[i][j] += mat[i][k] * m.mat[k][j];
            }
        }
        return temp;
    }

    friend istream &operator>>(istream &input, Matrix &m) {
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.col; j++)   input >> m.mat[i][j];
        }
        return input;
    }

    friend ostream &operator<<(ostream &output, const Matrix &m) {
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.col; j++)   output << m.mat[i][j] << "\t";
            output << endl;
        }
        return output;
    }
};

int main() {
    int r, c;
    cout << "Enter the number of rows and columns of the matrix: ";
    cin >> r >> c;
    Matrix m1(r, c), m2(r, c), m3(r, c);
    cout << "Enter the elements of the first matrix: " << endl;
    cin >> m1;
    cout << "Enter the elements of the second matrix: " << endl;
    cin >> m2;
    m3 = m1 + m2;
    cout << "\nAddition:"<<endl;
    cout << m3 << endl;
    cout << "\nMultiplication:"<<endl;
    m3 = m1 * m2;
    cout << m3 << endl;
    return 0;
}