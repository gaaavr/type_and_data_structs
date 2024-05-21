//
// Created by ssgavrilin on 09.03.2024.
//

#ifndef LAB_4_MATRIX_H
#define LAB_4_MATRIX_H

#include <iostream>
using namespace std;

typedef struct {
    int **matrix;
    int rows;
    int cols;
    vector<int> an;
    int *d;
    vector<int> nr;
    vector<int> nc;
    int *jr;
    int *jc;
} matrix;

void packMatrix(matrix &);
void unpackMatrix(matrix &);
matrix sumPackMatrix(matrix &, matrix &);
void printPackMatrix(matrix);
matrix sumPackMatrixExcessive(matrix &, matrix &);

#endif //LAB_4_MATRIX_H
