//
// Created by ssgavrilin on 24.03.2024.
//
#include "iostream"
#include "infix_to_postfix.h"
#include <map>
#include "calculate_opz.h"

using namespace std;

map<const char *, bool> allowedInfixChars = {
        {"+",   true},
        {"-",   true},
        {"*",   true},
        {"/",   true},
        {"^",   true},
        {"sin", true},
        {"cos", true},
        {"x",   true},
        {"(",   true},
        {")",   true},
};

map<const char *, int> operationPriorities = {
        {"+",   1},
        {"-",   1},
        {"*",   2},
        {"/",   2},
        {"^",   3},
        {"sin", 4},
        {"cos", 4},
};

bool validate(const char **infix, int infix_size);

void convertInfixToPostfix(const char **infix, int infix_size, response_infix &r) {
    if (!validate(infix, infix_size)) {
        return;
    };

    int result_size = 0;
    const char **opz = new const char *[infix_size];

    str_stack *st = new str_stack(infix_size);

    // Переводим из инфиксной формы в постфиксную
    for (int i = 0; i < infix_size; ++i) {
        // Если это число или переменная, кладём его в массив ОПЗ
        if (isNumber(infix[i]) || infix[i] == "x") {
            opz[result_size] = infix[i];
            result_size++;
            // Если это открывающая скобка, кладём её в стек
        } else if (infix[i] == "(") {
            if (!st->push(infix[i])) {
                return;
            }
            // Если это закрывающая скобка, пытаемся достать из стека все элементы, пока не найдём открывающую скобку
        } else if (infix[i] == ")") {
            while (!st->isEmpty() && st->getTopElement() != "(") {
                if (!st->pop(opz[result_size])) {
                    return;
                }

                result_size++;
            }

            // Просто выкидываем открывающую скобку после получения всех элементов под ней
            const char *bracket;
            if (!st->pop(bracket)) {
                return;
            }

            if (bracket != "(") {
                cout << "В инфиксной форме выражения неккоректно расставлены скобки" << endl;
                return;
            }
        } else {
            // Если стек пустой или последний элемент в нём открывабщая скобка, то кладём текущий элемент в стек
            if (st->isEmpty() || st->getTopElement() == "(") {
                if (!st->push(infix[i])) {
                    return;
                }
                // Если стек не пуст и верхний элемент операция, то сравниваем их вес
                // и если в стеке операция с меньшим весом, то кладём в стек текущую операцию
            } else {
                map<const char *, int>::iterator it, it_2;
                it = operationPriorities.find(st->getTopElement());
                it_2 = operationPriorities.find(infix[i]);

                if (it == operationPriorities.end()) {
                    cout << "Не найден приоритет для операции " << st->getTopElement() << endl;
                    return;
                }

                if (it_2 == operationPriorities.end()) {
                    cout << "Не найден приоритет для операции " << infix[i] << endl;
                    return;
                }

                if (it->second < it_2->second) {
                    if (!st->push(infix[i])) {
                        return;
                    }
                } else {
                    while (!st->isEmpty() && (st->getTopElement() != "(") && it!=operationPriorities.end() && it->second >= it_2->second) {
                        if (!st->pop(opz[result_size])) {
                            return;
                        }

                        result_size++;

                        if (!st->isEmpty()){
                            it = operationPriorities.find(st->getTopElement());
                        }
                    }

                    if (!st->push(infix[i])) {
                        return;
                    }
                }
            }
        }
    }

    while (!st->isEmpty()) {
        if (!st->pop(opz[result_size])) {
            return;
        }

        result_size++;
    }

    r.success = true;
    r.result_size = result_size;
    r.result = opz;

    st->free();
}

bool validate(const char **infix, int infix_size) {
    int counter = 0;
    for (int i = 0; i < infix_size; ++i) {
        if (infix[i] == "(") {
            counter++;
            continue;
        }

        if (infix[i] == ")") {
            counter--;
            continue;
        }

        if (allowedInfixChars.find(infix[i]) == allowedInfixChars.end() && !isNumber(infix[i]) &&
            (operationPriorities.find(infix[i]) == operationPriorities.end())) {
            cout << "Неподдерживаемый токен " << infix[i] << endl;
            return false;
        };

    }

    if (counter != 0) {
        cout << "В инфиксной форме выражения неккоректно расставлены скобки" << endl;
        return false;
    }

    return true;
}

void printResponseInfix(response_infix r) {
    char *success = "false";
    if (r.success) {
        success = "true";
    }

    cout << "Успех: " << success << endl << "Ответ: ";

    for (int i = 0; i < r.result_size; ++i) {
        cout << r.result[i] << " ";
    }
    cout << endl;
}