//
// Created by ssgavrilin on 24.03.2024.
//

#include "calculate_opz.h"
#include <iomanip>

#include "iostream"

using namespace std;

void printFuncTable(const char **opz, const int size_opz) {
    cout << "Введите Xmin, Xmax и h для вычисления таблицы значений функции от переменной x:" << endl;
    double x, x_min, x_max, h;
    cin >> x_min >> x_max >> h;

    // Создание файла для записи табилцы с полученными значениями функции
    FILE *table = fopen("table", "w");
    if (table  == NULL) {
        cout<<"Ошибка при создании файла для записи таблицы с результатами расчёта функции"<<endl;
        exit(1);
    }

    fprintf(table, "  x   |   f(x)   \n-----------------\n");

    for (x = x_min; x <=x_max; x += h) {
        response r = {
                .success=false,
                .result=0,
        };

        stack *st=new stack(size_opz);
        calculate(st, opz, size_opz, r, x);

        if (r.success){
            fprintf(table, "%0.3lf | %0.3lf \n", x, r.result);
        } else{
            fprintf(table, "%0.3lf | - \n", x);
        }

        st->free();
    }

    if (fabs(x - x_max-h)>0.000001) {
        response r = {
                .success=false,
                .result=0,
        };

        stack *st=new stack(size_opz);
        calculate(st, opz, size_opz, r, x_max);

        if (r.success){
            fprintf(table, "%0.3lf | %0.3lf \n", x_max, r.result);
        } else{
            fprintf(table, "%0.3lf | - \n", x_max);
        }

        st->free();
    }

    cout<<"Результаты вычислений записаны в файл table"<<endl;
    fclose(table);
}