#include <cstdio>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_bessel.h>
#include <sys/time.h>

typedef struct {
    int **matrix;
    int rows;
    int cols;
} matrix;

matrix createMatrix(int, int);

void printMatrix(matrix);

matrix multiplyMatrixWithStdAlg(matrix, matrix);

matrix multiplyMatrixWithVinogradAlg(matrix, matrix);

void compareMatrices(matrix, matrix);

void firstMode();

matrix newRandomMatrix(int, int);

void secondMode();

int main() {

    int mode;
    printf("Введите режим работы программы:\n"
           "1 - ввод двух матриц и сравнение результатов их умножения разными алгоритмами\n"
           "2 - режим массированного замера процессорного времени расчёта произведения матриц разными алгоритмами\n");

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

// Создаёт матрицу с количеством строк равным rows и количеством столбоцов равным cols,
// значения нужно вводить самостоятельно
matrix createMatrix(int rows, int cols) {
    if (rows == 0 || cols == 0) {
        printf("Число строк и столбцов матрицы не должно быть меньше 1");
        exit(1);
    }

    int **two_d_arr;

    two_d_arr = new int *[rows];

    printf("Введите последовательно %d элементов матрицы:\n", rows * cols);
    for (int i = 0; i < rows; i++) {
        two_d_arr[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            scanf("%d", &two_d_arr[i][j]);
        }
    }

    matrix m = {
            .matrix = two_d_arr,
            .rows =  rows,
            .cols =  cols,
    };

    return m;
}

// Выводит последовательно все элементы матрицы
void printMatrix(matrix m) {
    printf("Результирующая матрица %dx%d:\n", m.rows, m.cols);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            printf("%d ", m.matrix[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

// Стандартный алгоритм умножения матриц
matrix multiplyMatrixWithStdAlg(matrix matrix_A, matrix matrix_B) {
    matrix result_m;
    result_m.rows = 0;
    result_m.cols = 0;

    if (matrix_A.cols != matrix_B.rows) {
        printf("Матрицы нельзя умножить\n");
        exit(1);
    }

    int **matrix_C = new int *[matrix_A.rows];

    for (int i = 0; i < matrix_A.rows; i++) {
        matrix_C[i] = new int[matrix_B.cols];

        for (int j = 0; j < matrix_B.cols; j++) {
            matrix_C[i][j] = 0;

            for (int k = 0; k < matrix_A.cols; k++) {
                matrix_C[i][j] += matrix_A.matrix[i][k] * matrix_B.matrix[k][j];
            }
        }
    }

    result_m.matrix = matrix_C;
    result_m.rows = matrix_A.rows;
    result_m.cols = matrix_B.cols;

    return result_m;
}

// Алгоритм Винограда умножения матриц
matrix multiplyMatrixWithVinogradAlg(matrix matrix_A, matrix matrix_B) {
    matrix result_m;
    result_m.rows = 0;
    result_m.cols = 0;

    if (matrix_A.cols != matrix_B.rows) {
        return result_m;
    }

    int **matrix_C = new int *[matrix_A.rows];

    int *mulH = new int[matrix_A.rows];
    for (int i = 0; i < matrix_A.rows; i++) {
        mulH[i] = 0;
        for (int j = 1; j < matrix_A.cols; j += 2) {
            mulH[i] += (matrix_A.matrix[i][j - 1] * matrix_A.matrix[i][j]);
        }
    }

    int *mulV = new int[matrix_B.cols];
    for (int i = 0; i < matrix_B.cols; i++) {
        mulV[i] = 0;
        for (int j = 1; j < matrix_B.rows; j += 2) {
            mulV[i] += (matrix_B.matrix[j - 1][i] * matrix_B.matrix[j][i]);
        }
    }

    for (int i = 0; i < matrix_A.rows; i++) {
        matrix_C[i] = new int[matrix_B.cols];

        for (int j = 0; j < matrix_B.cols; j++) {

            matrix_C[i][j] = -mulH[i] - mulV[j];

            for (int k = 1; k < matrix_A.cols; k += 2) {
                matrix_C[i][j] +=
                        (matrix_A.matrix[i][k - 1] + matrix_B.matrix[k][j]) *
                        (matrix_A.matrix[i][k] + matrix_B.matrix[k - 1][j]);

            }
        }
    }

    if (matrix_A.cols % 2 == 1) {
        for (int i = 0; i < matrix_A.rows; i++) {
            for (int j = 0; j < matrix_B.cols; j++) {
                matrix_C[i][j] += matrix_A.matrix[i][matrix_A.cols - 1] * matrix_B.matrix[matrix_A.cols - 1][j];
            }
        }
    }

    result_m.matrix = matrix_C;
    result_m.rows = matrix_A.rows;
    result_m.cols = matrix_B.cols;

    delete[] mulH;
    delete[] mulV;
    return result_m;
}

void compareMatrices(matrix matrix_A, matrix matrix_B) {
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

void firstMode() {
    int first_m_rows, first_m_cols, sec_m_rows, sec_m_cols;

    printf("Введите количество строк первой матрицы:\n");
    scanf("%d", &first_m_rows);
    printf("Введите количество колонок первой матрицы:\n");
    scanf("%d", &first_m_cols);
    matrix matrix_A = createMatrix(first_m_rows, first_m_cols);

    printf("Введите количество строк второй матрицы:\n");
    scanf("%d", &sec_m_rows);
    printf("Введите количество колонок второй матрицы:\n");
    scanf("%d", &sec_m_cols);
    matrix matrix_B = createMatrix(sec_m_rows, sec_m_cols);

    matrix result_std_matrix = multiplyMatrixWithStdAlg(matrix_A, matrix_B);
    matrix result_vng_matrix = multiplyMatrixWithVinogradAlg(matrix_A, matrix_B);

    compareMatrices(result_std_matrix, result_vng_matrix);

    printf("Результат умножения матриц обычным алгоритмом: \n");
    printMatrix(result_std_matrix);

    printf("Результат умножения матриц алгоритмом Винограда: \n");
    printMatrix(result_vng_matrix);


    delete[] matrix_A.matrix;
    delete[] matrix_B.matrix;
    delete[] result_vng_matrix.matrix;
    delete[] result_std_matrix.matrix;
}

void secondMode() {
    // Создание файла для записи данных по выполнения алгоритмов,
    // чтобы в дальнейшем отрисовать по этим данным графики
    FILE *stdAlgFile = fopen("std_alg.txt", "w");
    if (stdAlgFile == NULL) {
        printf("Ошибка при создании файла данных для стандартного алгоритма\n");
        exit(1);
    }

    FILE *vngAlgFile = fopen("Vinograd_alg.txt", "w");
    if (vngAlgFile == NULL) {
        printf("Ошибка при создании файла данных для алгоритма Винограда\n");
        exit(1);
    }

    clock_t t;
    // Последовательно получаем матрицы размером i на i,
    // элементы матрицы - рандомные числа от 0 до 100.
    for (int i = 100; i < 501; i += 100) {
        double stdAlgAvgProcTime = 0.0, vngAlgAvgProcTime = 0.0;

        // Во вложенном цикле 10 раз умножаем матрицу обычным алгоритмом
        // и алгоритмом Винограда.
        for (int j = 0; j < 10; j++) {
            matrix random_matrix = newRandomMatrix(i, i);
            // Замеряем для каждого из алгоритмов затраченное процессорное время.
            // Функция взята из https://cplusplus.com/reference/ctime/clock/ .
            t = clock();
            matrix std_matrix=multiplyMatrixWithStdAlg(random_matrix, random_matrix);
            t = clock() - t;

            stdAlgAvgProcTime += ((double) t);

            t = clock();
            matrix vng_matrix=multiplyMatrixWithVinogradAlg(random_matrix, random_matrix);
            t = clock() - t;

            vngAlgAvgProcTime += ((double) t);

            delete[]random_matrix.matrix;
            delete[]std_matrix.matrix;
            delete[]vng_matrix.matrix;
        }

        // Замеренное процессорное время представлено в тактах.
        // Чтобы получить секунды. нужно разделить на 1 000 000
        // Чтобы получить миллисекунды, нужно разделить на 1000.
        // Чтобы получить среднее арифметическое, нужно разделить на 10.
        // Полученные данные в миллисекундах записываем в файлы.
        fprintf(stdAlgFile, "%d %f\n", i, stdAlgAvgProcTime / 10000);
        fprintf(vngAlgFile, "%d %f\n", i, vngAlgAvgProcTime / 10000);
    }


    // Закрытие файла с данными
    fclose(stdAlgFile);
    fclose(vngAlgFile);

    FILE *gnuplotFile = fopen("plot.gnu", "w");
    if (gnuplotFile == NULL) {
        printf("Ошибка при создании файла GNUplot\n");
        exit(1);
    }

    // Запись команд GNUplot в файл
    fprintf(gnuplotFile, "set term png\n");
    fprintf(gnuplotFile, "set output 'graphics.png'\n");
    fprintf(gnuplotFile, "set xlabel 'Количество элементов в матрице, N'\n");
    fprintf(gnuplotFile, "set ylabel 'Время выполнения алгоритма, мс'\n");
    fprintf(gnuplotFile, "set xrange [0:700]\n");
    fprintf(gnuplotFile, "set yrange [0:600]\n");
    fprintf(gnuplotFile, "plot 'Vinograd_alg.txt' with lines, 'std_alg.txt' with lines\n");

    // Закрытие файла с командами GNUplot
    fclose(gnuplotFile);

    // Запуск GNUplot для построения графика
    system("gnuplot plot.gnu");

    printf("Графики успешно построены в файле graphics.png\n");
}

matrix newRandomMatrix(int rows, int cols) {
    if (rows == 0 || cols == 0) {
        printf("Число строк и столбцов матрицы не должно быть меньше 1");
        exit(1);
    }

    int **two_d_arr;

    two_d_arr = new int *[rows];

    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        two_d_arr[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            two_d_arr[i][j] = (rand() % 100);
        }
    }

    matrix m = {
            .matrix = two_d_arr,
            .rows =  rows,
            .cols =  cols,
    };

    return m;
}
