#include <cstdio>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_bessel.h>
#include <sys/time.h>
#include "algoritms.h"
#include "helpers.h"

void firstMode();

void secondMode();

int main() {
    int mode;
    printf("Введите режим работы программы:\n"
           "1 - ввод двух строк и сравнение результатов поиска минимального расстояния разными алгоритмами\n"
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

void firstMode() {
    wstring str_1 = L"qwerty";
    wstring str_2 = L"qewtry";
    int len_1 = (int) str_1.length();
    int len_2 = (int) str_2.length();

    int min_steps_1 = levenshteinWithoutRecursive(str_1, str_2, len_1, len_2);
    printf("[Расстояние Левенштейна без рекурсии] минимальное количество шагов: %d\n", min_steps_1);

    int min_steps_2 = levenshteinWithRecursive(str_1, str_2, len_1, len_2);
    printf("[Расстояние Левенштейна с рекурсией] минимальное количество шагов: %d\n", min_steps_2);

    int min_steps_3 = levenshteinWithCacheRecursive(str_1, str_2, len_1, len_2, NULL);
    printf("[Расстояние Левенштейна с рекурсией и кэшом] минимальное количество шагов: %d\n", min_steps_3);

    int min_steps_4 = levenshteinDamerauDistance(str_1, str_2, len_1, len_2);
    printf("[Расстояние Левенштейна-Дамерау] минимальное количество шагов: %d\n\n", min_steps_4);

    if (min_steps_1 == min_steps_2 && min_steps_1 == min_steps_3 && min_steps_1 == min_steps_4) {
        printf("Различий между результатами расчётов нет\n\n");
    } else {
        printf("Результаты расчёта различаются\n");
    }

    levenshteinData m = createLevenshteinMatrix(str_1, str_2, len_1, len_2);
    printMatrix(m);
    reverse(m.chainOperations.begin(), m.chainOperations.end());
    printf("Цепочка операций: %s\n", m.chainOperations.c_str());
    delete[] m.matrix;
}

void secondMode() {
    // Создание файла для записи данных по выполнения алгоритмов,
    // чтобы в дальнейшем отрисовать по этим данным графики
    FILE *stdAlgFile = fopen("lev_std_alg.txt", "w");
    if (stdAlgFile == NULL) {
        printf("Ошибка при создании файла данных для стандартного алгоритма Левенштейна\n");
        exit(1);
    }

    FILE *recAlgFile = fopen("rec_lev_alg.txt", "w");
    if (recAlgFile == NULL) {
        printf("Ошибка при создании файла данных для алгоритма Левенштейна через рекурсию\n");
        exit(1);
    }

    FILE *recCacheAlgFile = fopen("rec_cache_lev_alg.txt", "w");
    if (recCacheAlgFile == NULL) {
        printf("Ошибка при создании файла данных для алгоритма Левенштейна через рекурсию с кэшом\n");
        exit(1);
    }

    FILE *damerauAlgFile = fopen("damerau_alg.txt", "w");
    if (damerauAlgFile == NULL) {
        printf("Ошибка при создании файла данных для алгоритма Дамерау-Левенштейна\n");
        exit(1);
    }

    clock_t t;
    // Последовательно получаем рандомные строки размером i,
    // элементы строки - строки латиницы и кириллицы
    for (int i = 1; i < 11; i += 1) {
        double stdAlgAvgProcTime = 0.0, recAlgAvgProcTime = 0.0,
                recCacheAlgAvgProcTime = 0.0, damerauAlgAvgProcTime = 0.0;
        srand(time(NULL));
        wstring str_1 = getRandomString(i, char(rand() % 26 + 'a'));
        wstring str_2 = getRandomString(i, char(rand() % 26 + 'a'));

        // Во вложенном цикле 10 раз сравниваем строки по каждому алгоритму
        for (int j = 0; j < 10; j++) {

            // Замеряем для каждого из алгоритмов затраченное процессорное время.
            // Функция взята из https://cplusplus.com/reference/ctime/clock/ .
            t = clock();
            levenshteinWithoutRecursive(str_1, str_2, i, i);
            t = clock() - t;

            stdAlgAvgProcTime += ((double) t);

            t = clock();
            levenshteinWithRecursive(str_1, str_2, i, i);
            t = clock() - t;

            recAlgAvgProcTime += ((double) t);

            t = clock();
            levenshteinWithCacheRecursive(str_1, str_2, i, i, NULL);
            t = clock() - t;

            recCacheAlgAvgProcTime += ((double) t);

            t = clock();
            levenshteinDamerauDistance(str_1, str_2, i, i);
            t = clock() - t;

            damerauAlgAvgProcTime += ((double) t);
        }

        // Замеренное процессорное время представлено в тактах.
        // Чтобы получить секунды, нужно разделить на 1 000 000
        // => чтобы получить миллисекунды, нужно разделить на 1000.
        // Чтобы получить среднее арифметическое, нужно разделить на 10.
        // Полученные данные в миллисекундах записываем в файлы.
        fprintf(stdAlgFile, "%d %f\n", i, stdAlgAvgProcTime / 10000);
        fprintf(recAlgFile, "%d %f\n", i, recAlgAvgProcTime / 10000);
        fprintf(recCacheAlgFile, "%d %f\n", i, recCacheAlgAvgProcTime / 10000);
        fprintf(damerauAlgFile, "%d %f\n", i, damerauAlgAvgProcTime / 10000);
    }


    // Закрытие файла с данными
    fclose(stdAlgFile);
    fclose(recAlgFile);
    fclose(recCacheAlgFile);
    fclose(damerauAlgFile);

    FILE *gnuplotFile = fopen("plot.gnu", "w");
    if (gnuplotFile == NULL) {
        printf("Ошибка при создании файла GNUplot\n");
        exit(1);
    }

    // Запись команд GNUplot в файл для всех алгоритмов
    fprintf(gnuplotFile, "set term png\n");
    fprintf(gnuplotFile, "set output 'graphics.png'\n");
    fprintf(gnuplotFile, "set xlabel 'Количество символов в строках'\n");
    fprintf(gnuplotFile, "set ylabel 'Время выполнения алгоритма, мс'\n");
    fprintf(gnuplotFile, "set xrange [0:12]\n");
    fprintf(gnuplotFile, "set yrange [0:0.02]\n");
    fprintf(gnuplotFile, "plot 'lev_std_alg.txt' with lines, "
                         "'rec_cache_lev_alg.txt' with lines, 'damerau_alg.txt' with lines\n");

    // Запись команд GNUplot в файл для алгоритма рекурсии
    fprintf(gnuplotFile, "set term png\n");
    fprintf(gnuplotFile, "set output 'recursive_graphics.png'\n");
    fprintf(gnuplotFile, "set xlabel 'Количество символов в строках'\n");
    fprintf(gnuplotFile, "set ylabel 'Время выполнения алгоритма, мс'\n");
    fprintf(gnuplotFile, "set xrange [0:12]\n");
    fprintf(gnuplotFile, "set yrange [0:1000]\n");
    fprintf(gnuplotFile, "plot 'rec_lev_alg.txt' with lines\n");

    // Закрытие файла с командами GNUplot
    fclose(gnuplotFile);

    // Запуск GNUplot для построения графика
    system("gnuplot plot.gnu");

    printf("Графики успешно построены в файле graphics.png\n");
}