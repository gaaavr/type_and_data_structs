//
// Created by ssgavrilin on 24.03.2024.
//

#include <cmath>
#include "iostream"
#include "calculate_opz.h"
#include <map>

using namespace std;

map<const char *, bool> allowedChars = {
        {"+",   true},
        {"-",   true},
        {"*",   true},
        {"/",   true},
        {"^",   true},
        {"sin", true},
        {"cos", true},
        {"x",   true},
};

bool isNumber(const char *chars) {
    int i = 0;
    while (chars[i] != '\0') {
        if (!isdigit(chars[i])) {
            return false;
        }
        i++;
    }

    return true;
}

bool elementIsValid(const char *chars) {
    if (allowedChars.find(chars) == allowedChars.end() && !isNumber(chars)) {
        return false;
    };

    return true;
}

bool validateOpzArray(const char **arr, const int arrSize) {
    if (arrSize == 0) {
        cout << "Размер массива строк ОПЗ равен нулю" << endl;
        return false;
    }

    for (int i = 0; i < arrSize; ++i) {
        if (!elementIsValid(arr[i])) {
            cout << "Элемент массива " << arr[i] << " не валиден" << endl;
        };
    }

    return true;
}

void calculate(stack *st, const char **opz, const int size_opz, response &r, double x) {
    for (int i = 0; i < size_opz; ++i) {
        if (isNumber(opz[i])) {
            if (!st->push((double) stoi(opz[i]))){
                return;
            };

            continue;
        }

        if (opz[i] == "x") {
            if (!st->push(x)){
                return;
            };

            continue;
        }

        if (opz[i] == "+") {
            double operand_1, operand_2;
            if (!st->pop(operand_1)){
                return;
            };

            if (!st->pop(operand_2)){
                return;
            };

            if (!st->push(operand_1 + operand_2)){
                return;
            };

            continue;
        }

        if (opz[i] == "-") {
            double operand_1, operand_2;
            if (!st->pop(operand_1)){
                return;
            };

            if (!st->pop(operand_2)){
                return;
            };

            if (!st->push(operand_2 - operand_1)){
                return;
            };

            continue;
        }

        if (opz[i] == "*") {
            double operand_1, operand_2;
            if (!st->pop(operand_1)){
                return;
            };

            if (!st->pop(operand_2)){
                return;
            };


            if (!st->push(operand_1 * operand_2)){
                return;
            };

            continue;
        }

        if (opz[i] == "/") {
            double operand_1, operand_2;
            if (!st->pop(operand_1)){
                return;
            };

            if (operand_1 == 0) {
                cout << "ошибка: попытка разделить на 0" << endl;
                return;
            }

            if (!st->pop(operand_2)){
                return;
            };

            if (!st->push(operand_2 / operand_1)){
                return;
            };

            continue;
        }

        if (opz[i] == "^") {
            double operand_1, operand_2;
            if (!st->pop(operand_1)){
                return;
            };

            if (!st->pop(operand_2)){
                return;
            };


            // проверка на возведение нуля в отрицательную степень
            if (operand_2 == 0 && operand_1 < 0) {
                cout << "ошибка: попытка возвести 0 в отрицательную степень" << endl;
                return;
            }

            // проверка на возведение отрицательное числа в нецелую степень
            if (operand_2 < 0 && (operand_1 != (int) operand_1)) {
                cout << "ошибка: попытка возвести отрицательное число в нецелую степень" << endl;
                return;
            }

            if (!st->push(pow(operand_2, operand_1))){
                return;
            };

            continue;
        }

        if (opz[i] == "sin") {
            double operand_1;
            if (!st->pop(operand_1)){
                return;
            };

            if (!st->push(sin(operand_1))){
                return;
            };

            continue;
        }

        if (opz[i] == "cos") {
            double operand_1;
            if (!st->pop(operand_1)){
                return;
            };

            if (!st->push(cos(operand_1))){
                return;
            };

            continue;
        }

        cout << "ошибка: неподдерживаемый символ " << opz[i] << endl;
        return;
    }

    st->pop(r.result);
    if (!st->isEmpty()){
        cout << "ошибка: в стеке содержится более 1 элемента после вычислений"<< endl;
        return;
    }

    r.success=true;
}


void printResponse(response r){
    char * success = "false";
    if (r.success){
        success="true";
    }

    cout<<"Успех: "<<success<<endl<<"Ответ: "<< r.result<<endl;
}