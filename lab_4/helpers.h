#ifndef LAB_4_HELPERS_H
#define LAB_4_HELPERS_H

#include <iostream>
#include "matrix.h"

matrix readMatrixFromFile(char *);
void printMatrix(matrix);
matrix sumMatrix(matrix &, matrix &);
matrix mulMatrix(matrix &a, matrix &b);
void compareMatrices(matrix &, matrix &);

#endif //LAB_4_HELPERS_H
