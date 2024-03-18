//
// Created by ssgavrilin on 24.02.2024.
//

#ifndef LAB_3_HELPERS_H
#define LAB_3_HELPERS_H

#include <string>

using namespace std;

typedef struct {
    int **matrix;
    int rows;
    int cols;
    string chainOperations;
} levenshteinData;

levenshteinData createLevenshteinMatrix(wstring, wstring, int, int);

string getChainOperations(levenshteinData);

wstring getRandomString(int, char);

void printMatrix(levenshteinData);

#endif //LAB_3_HELPERS_H
