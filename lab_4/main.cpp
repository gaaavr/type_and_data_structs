#include "matrix_sum_krm.h"
#include "helpers.h"
#include "matrix.h"

void firstMode();

void secondMode();

int main() {
    int mode;
    printf("Введите режим работы программы:\n"
           "1 - сложение сжатых матриц по схеме Дженнинга\n"
           "2 - сложение и умножение сжатых матриц по схеме Рейнбольдта - Местеньи\n");

    scanf("%d", &mode);

    switch (mode) {
        case 1:
            firstMode();
            break;
        case 2:
            secondMode();
            break;
        default:
            printf("Режима с номером %d не существует", mode);
    }


    return 0;
}

void firstMode() {
    matrix matrix_a = readMatrixFromFile("../matrix_a");
    printMatrix(matrix_a);
    packMatrix(matrix_a);
    printPackMatrix(matrix_a);
    cout << endl;

    matrix matrix_b = readMatrixFromFile("../matrix_b");
    printMatrix(matrix_b);
    packMatrix(matrix_b);
    printPackMatrix(matrix_b);

    matrix matrix_c = sumPackMatrix(matrix_a, matrix_b);
    printPackMatrix(matrix_c);

    unpackMatrix(matrix_c);
    printMatrix(matrix_c);

    matrix matrix_d = sumMatrix(matrix_a, matrix_b);
    printMatrix(matrix_d);

    compareMatrices(matrix_c, matrix_d);

    delete[] matrix_a.matrix;
    matrix_a.an.clear();
    delete matrix_a.d;

    delete[] matrix_b.matrix;
    matrix_b.an.clear();
    delete matrix_b.d;

    delete[] matrix_c.matrix;
    matrix_c.an.clear();
    delete matrix_c.d;

    delete[] matrix_d.matrix;
}

void secondMode() {
    // Сложение сжатых матрицы
    cout<<"[СЛОЖЕНИЕ СЖАТЫХ МАТРИЦ]";
    matrix matrix_rm_1 = readMatrixFromFile("../matrix_rm_1");

    packMatrixByKrm(matrix_rm_1);

    cout << endl<< endl << "[Сжатая матрица №1]";
    printPackMatrixByKRM(matrix_rm_1);

    matrix matrix_rm_2 = readMatrixFromFile("../matrix_rm_2");

    packMatrixByKrm(matrix_rm_2);

    cout<< endl << endl << "[Сжатая матрица №2]";
    printPackMatrixByKRM(matrix_rm_2);

    matrix sum_matrix_krm = sumPackMatrixByKRM(matrix_rm_1, matrix_rm_2);
    cout << endl<< endl << "[Результирующая сжатая матрица после сложения]";
    printPackMatrixByKRM(sum_matrix_krm);
    unpackMatrixByKrm(sum_matrix_krm);

    cout << endl<< endl << "[Обычная матрица после сложения]"<<endl;
    matrix sum_matrix=sumMatrix(matrix_rm_1, matrix_rm_2);
    printMatrix(sum_matrix);

    compareMatrices(sum_matrix_krm, sum_matrix);

    // Умножение сжатых матриц
    cout<<"[УМНОЖЕНИЕ СЖАТЫХ МАТРИЦ]"<<endl;
    matrix matrix_rm_3 = readMatrixFromFile("../mul_1");

    packMatrixByKrm(matrix_rm_3);

    cout << endl << "[Сжатая матрица №3]";
    printPackMatrixByKRM(matrix_rm_3);

    matrix matrix_rm_4 = readMatrixFromFile("../mul_2");

    packMatrixByKrm(matrix_rm_4);

    cout<< endl << endl << "[Сжатая матрица №4]";
    printPackMatrixByKRM(matrix_rm_4);

    cout << endl<< endl << "[Результирующая сжатая матрица после умножения]";
    matrix mul_matrix_krm=mulPackMatrixByKRM(matrix_rm_3, matrix_rm_4);
    printPackMatrixByKRM(mul_matrix_krm);
    unpackMatrixByKrm(mul_matrix_krm);

    cout << endl<< endl << "[Обычная матрица после умножения]"<<endl;
    matrix mul_matrix=mulMatrix(matrix_rm_3, matrix_rm_4);
    printMatrix(mul_matrix);

    compareMatrices(mul_matrix_krm, mul_matrix);

    // Очистим динамическую память
    delete[] matrix_rm_1.matrix;
    matrix_rm_1.an.clear();
    matrix_rm_1.nr.clear();
    matrix_rm_1.nc.clear();
    delete matrix_rm_1.jr;
    delete matrix_rm_1.jc;

    delete[] matrix_rm_2.matrix;
    matrix_rm_2.an.clear();
    matrix_rm_2.nr.clear();
    matrix_rm_2.nc.clear();
    delete matrix_rm_2.jr;
    delete matrix_rm_2.jc;

    delete[] sum_matrix.matrix;

    delete[] sum_matrix_krm.matrix;
    sum_matrix_krm.an.clear();
    sum_matrix_krm.nr.clear();
    sum_matrix_krm.nc.clear();
    delete sum_matrix_krm.jr;
    delete sum_matrix_krm.jc;

    delete[] matrix_rm_3.matrix;
    matrix_rm_3.an.clear();
    matrix_rm_3.nr.clear();
    matrix_rm_3.nc.clear();
    delete matrix_rm_3.jr;
    delete matrix_rm_3.jc;

    delete[] matrix_rm_4.matrix;
    matrix_rm_4.an.clear();
    matrix_rm_4.nr.clear();
    matrix_rm_4.nc.clear();
    delete matrix_rm_4.jr;
    delete matrix_rm_4.jc;

    delete[] mul_matrix.matrix;

    delete[] mul_matrix_krm.matrix;
    mul_matrix_krm.an.clear();
    mul_matrix_krm.nr.clear();
    mul_matrix_krm.nc.clear();
    delete mul_matrix_krm.jr;
    delete mul_matrix_krm.jc;
}
