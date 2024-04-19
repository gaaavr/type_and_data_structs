//
// Created by ssgavrilin on 24.03.2024.
//

#ifndef LAB_5_INFIX_TO_POSTFIX_H
#define LAB_5_INFIX_TO_POSTFIX_H

#include "iostream"

using namespace std;

struct response_infix {
    bool success;
    const char **result;
    int result_size;
};

void convertInfixToPostfix(const char **, int, response_infix &);
void printResponseInfix(response_infix);

class str_stack {
private:
    const char **values;
    unsigned int currentSize;
    int capacity;

public:
    bool push(const char *value) {
        if (isFull()) {
            cout << "Нельзя добавить значение в стек: он полон" << endl;
            return false;
        }

        values[currentSize] = value;
        currentSize++;

        return true;
    }

    bool pop(const char *&value) {
        if (isEmpty()) {
            cout << "Нельзя взять значение из стека: он пуст" << endl;
            return false;
        }

        currentSize--;

        value = values[currentSize];

        return true;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == capacity;
    }

    const char *getTopElement() {
        return values[currentSize - 1];
    }

    void display() {
        cout << "Текущие значения в стеке:" << endl;

        for (int i = 0; i < currentSize; ++i) {
            cout << values[i] << " ";
        }

        cout << endl;
    }

    void free() {
        delete values;
    }

    str_stack(const int cap) {
        values = new const char *[cap];
        capacity = cap;
        currentSize = 0;
    }
};


#endif //LAB_5_INFIX_TO_POSTFIX_H
