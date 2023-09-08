#include <iostream>
#include <vector>
#define n 4


int factorial(int x){

    return (x < 2) ? 1 : x * factorial (x - 1);
}


void table_inversions(int num, int w[]){
    int f;
    w[n-1] = 0;
    for (int i = 0; i < n - 1; i++){
        f = factorial(n-1-i);
        w[i] = num / f;
        num = num % f;
    }
}

void transposition(int w[], int p[]){
    std::vector<int> temp;
    for (int i = n - 1; i >= 0; i--){
        temp.insert(temp.begin() + w[i], i + 1);
    }
    for (int i = 0; i < n; ++i) {
        p[i] = temp[i];
    }
}

void fill_matrix(int matrix[n][n]){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = 1;
        }
    }
}

int sign(int w[]){
    int s = 0;
    for (int i = 0; i < n; ++i) {
        s += w[i];
    }
    return (s % 2) ? -1: 1;
}


void determinant(){
    int w[n], p[n];
    int matrix[n][n];
    long int det = 0, comp;
    fill_matrix(matrix);
    for (int i = 0; i < factorial(n); ++i) {
        comp = 1;
        table_inversions(i, w);
        transposition(w, p);
        for (int j = 0; j < n; ++j) {
            comp *= matrix[j][p[j] - 1];
        }
        det += sign(w)*comp;
    }
    std::cout << "Определитель матрицы = " << det << std::endl;
}


int main() {
    determinant();
    return 0;
