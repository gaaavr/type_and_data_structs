//
// Created by ssgavrilin on 24.02.2024.
//
#include "helpers.h"

wstring getRandomString(int size, char symbol) {
    wstring str;
    for (int i = 0; i < size; ++i) {
        str += symbol;
    }

    return str;
}

// Создаёт матрицу с результатами расчёта расстояния Левенштейна
levenshteinData createLevenshteinMatrix(wstring str_1, wstring str_2, int len_1, int len_2) {
    if (len_1 > len_2) {
        return createLevenshteinMatrix(str_2, str_1, len_2, len_1);
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

    levenshteinData m = {
            .matrix= matrix,
            .rows=len_2 + 1,
            .cols=len_1 + 1,
    };

    m.chainOperations = getChainOperations(m);

    return m;
}

// Выводит цепочку операций при сравнении строк
string getChainOperations(levenshteinData m) {
    int **matrix = m.matrix;
    int i = m.rows - 1, j = m.cols - 1;
    string chain = "";

    while (i != 0 || j != 0) {
        if (i != 0 && matrix[i][j] > matrix[i - 1][j]) {
            i--;
            chain += 'D';
            continue;
        }

        if (j != 0 && matrix[i][j] > matrix[i][j - 1]) {
            j--;
            chain += "I";
            continue;
        }

        if (j != 0 && i != 0 && matrix[i][j] > matrix[i - 1][j - 1]) {
            j--;
            i--;
            chain += 'R';
            continue;
        }

        if (j != 0 && i != 0 && matrix[i][j] == matrix[i - 1][j - 1]) {
            j--;
            i--;
            chain += 'M';
        }
    }

    return chain;
}

// Выводит последовательно все элементы матрицы
void printMatrix(levenshteinData m) {
    printf("Результирующая матрица %dx%d:\n", m.rows, m.cols);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            printf("%d ", m.matrix[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}
