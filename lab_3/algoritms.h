//
// Created by ssgavrilin on 24.02.2024.
//

#ifndef LAB_3_ALGORITMS_H
#define LAB_3_ALGORITMS_H

#include <string>

using namespace std;

int levenshteinWithoutRecursive(wstring, wstring, int, int);

int levenshteinWithRecursive(wstring, wstring, int, int);

int levenshteinWithCacheRecursive(wstring, wstring, int, int, int **);

int levenshteinDamerauDistance(wstring, wstring, int, int);

#endif //LAB_3_ALGORITMS_H
