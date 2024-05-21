#include "helpers.h"

// Функция для чтения матрицы из файла,
// на первой строке в файле должно быть
// указано количество строк и столбцов в матрице
matrix readMatrixFromFile(char *filepath) {
    FILE *matrix_file = fopen(filepath, "r");
    if (matrix_file == NULL) {
        cout << "Ошибка при чтении файла " << filepath << endl;
        exit(1);
    }
    matrix m;

    fscanf(matrix_file, "%d %d", &m.rows, &m.cols);

    m.matrix = new int *[m.rows];

    for (int i = 0; i < m.rows; ++i) {
        m.matrix[i] = new int[m.cols];

        for (int j = 0; j < m.cols; ++j) {
            fscanf(matrix_file, "%d", &m.matrix[i][j]); // Считываем элементы матрицы из файла
        }
    }

    fclose(matrix_file);

    return m;
}

// Выводит последовательно все элементы матрицы
void printMatrix(matrix m) {
    printf("Результирующая матрица %dx%d:\n", m.rows, m.cols);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            cout << m.matrix[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;
}

// Функция для сложения двух матриц
matrix sumMatrix(matrix &a, matrix &b) {
    matrix c;
    c.matrix = new int *[a.rows];
    c.rows = a.rows;
    c.cols = a.cols;

    for (int i = 0; i < a.rows; ++i) {
        c.matrix[i] = new int[a.cols];
        for (int j = 0; j < a.cols; ++j) {
            c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        }
    }

    return c;
}

// Функция для умножения двух матриц
matrix mulMatrix(matrix &a, matrix &b) {
    if (a.cols != b.rows) {
        cout << "Количество столбцов первой матрицы не равно количеству строк второй матрицы, умножение невозможно"
             << endl;
        exit(0);
    }

    matrix c;
    c.matrix = new int *[a.rows];
    c.rows = a.rows;
    c.cols = b.cols;

    for (int i = 0; i < a.rows; ++i) {
        c.matrix[i] = new int[b.cols];
        for (int j = 0; j < b.cols; ++j) {
            for (int k = 0; k < a.cols; k++) {
                c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }

    return c;
}

// Функция для сравнения двух матриц в стандартном виде
void compareMatrices(matrix &matrix_A, matrix &matrix_B) {
    if (matrix_A.rows != matrix_B.rows || matrix_A.cols != matrix_B.cols) {
        printf("Матрицы имеют разный размер: A[%dx%d]!=B[%dx%d]\n",
               matrix_A.rows, matrix_A.cols, matrix_B.rows, matrix_B.cols);

        return;
    }

    int counter = 0;

    for (int i = 0; i < matrix_A.rows; i++) {
        for (int j = 0; j < matrix_A.cols; j++) {
            if (matrix_A.matrix[i][j] != matrix_B.matrix[i][j]) {
                counter++;
                printf("A[%d][%d]!=B[%d][%d] (%d!=%d)\n",
                       i, j, i, j, matrix_A.matrix[i][j], matrix_B.matrix[i][j]);
            }
        }
    }

    if (counter == 0) {
        printf("Результирующие матрицы совпадают\n\n");
    } else {
        printf("Результирующие матрицы имеют %d отличий\n\n", counter);
    }
}
