//
// Created by ssgavrilin on 24.02.2024.
//
#include "algoritms.h"

int levenshteinWithoutRecursive(wstring str_1, wstring str_2, int len_1, int len_2) {
    if (len_1 == 0) {
        return len_2;
    }

    if (len_2 == 0) {
        return len_1;
    }

    if (len_1 > len_2) {
        return levenshteinWithoutRecursive(str_2, str_1, len_2, len_1);
    }

    int **matrix = new int *[len_2 + 1];
    matrix[0] = new int[len_1 + 1];

    for (int i = 0; i <= len_1; ++i) {
        matrix[0][i] = i;
    }

    for (int i = 1; i <= len_2; ++i) {
        matrix[i] = new int[len_1 + 1];
        matrix[i][0] = i;

        for (int j = 1; j <= len_1; ++j) {
            if (str_2[i - 1] != str_1[j - 1]) {
                matrix[i][j] = min(min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1), matrix[i - 1][j - 1] + 1);
            } else {
                matrix[i][j] = matrix[i - 1][j - 1];
            }
        }
    }

    int minSteps = matrix[len_2][len_1];

    delete[] matrix;

    return minSteps;
}

int levenshteinWithRecursive(wstring str_1, wstring str_2, int len_1, int len_2) {
    if (len_1 == 0) {
        return len_2;
    }

    if (len_2 == 0) {
        return len_1;
    }

    if (len_1 > len_2) {
        return levenshteinWithRecursive(str_2, str_1, len_2, len_1);
    }

    int cost = str_1[len_1 - 1] != str_2[len_2 - 1] ? 1 : 0;

    return min(min(levenshteinWithRecursive(str_1, str_2, len_1 - 1, len_2) + 1,
                   levenshteinWithRecursive(str_1, str_2, len_1, len_2 - 1) + 1),
               levenshteinWithRecursive(str_1, str_2, len_1 - 1, len_2 - 1) + cost);
}

int levenshteinWithCacheRecursive(wstring str_1, wstring str_2, int len_1, int len_2, int **matrix) {
    if (len_1 == 0) {
        return len_2;
    }

    if (len_2 == 0) {
        return len_1;
    }

    if (len_1 > len_2) {
        return levenshteinWithCacheRecursive(str_2, str_1, len_2, len_1, matrix);
    }


    if (!matrix) {
        matrix = new int *[len_1 + 1];
        for (int i = 0; i <= len_1; ++i) {
            matrix[i] = new int[len_2 + 1];
            for (int j = 0; j <= len_2; ++j) {
                matrix[i][j] = -1;
            }
        }
    }

    if (matrix[len_1][len_2] != -1) {
        return matrix[len_1][len_2];
    } else {
        int cost = str_1[len_1 - 1] != str_2[len_2 - 1] ? 1 : 0;

        matrix[len_1][len_2] = min(min(levenshteinWithCacheRecursive(str_1, str_2, len_1 - 1, len_2, matrix) + 1,
                                       levenshteinWithCacheRecursive(str_1, str_2, len_1, len_2 - 1, matrix) + 1),
                                   levenshteinWithCacheRecursive(str_1, str_2, len_1 - 1, len_2 - 1, matrix) + cost);

        return matrix[len_1][len_2];
    }
}

int levenshteinDamerauDistance(wstring str_1, wstring str_2, int len_1, int len_2) {
    if (len_1 == 0) {
        return len_2;
    }

    if (len_2 == 0) {
        return len_1;
    }

    if (len_1 > len_2) {
        return levenshteinDamerauDistance(str_2, str_1, len_2, len_1);
    }

    int **matrix = new int *[len_2 + 1];
    matrix[0] = new int[len_1 + 1];

    for (int i = 0; i <= len_1; ++i) {
        matrix[0][i] = i;
    }

    for (int i = 1; i <= len_2; ++i) {
        matrix[i] = new int[len_1 + 1];
        matrix[i][0] = i;

        for (int j = 1; j <= len_1; ++j) {
            int cost = str_2[i - 1] != str_1[j - 1];

            matrix[i][j] = min(min(matrix[i][j - 1] + 1, matrix[i - 1][j] + 1), matrix[i - 1][j - 1] + cost);

            if (i > 1 && j > 1 && str_1[i - 1] == str_2[j - 2] && str_1[i - 2] == str_2[j - 1])
                matrix[i][j] = min(matrix[i][j], matrix[i - 2][j - 2] + cost);
        }
    }

    int minSteps = matrix[len_2][len_1];

    delete[] matrix;

    return minSteps;
}
