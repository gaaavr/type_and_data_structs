//
// Created by ssgavrilin on 24.03.2024.
//
#ifndef LAB_5_CALCULATE_OPZ_H
#define LAB_5_CALCULATE_OPZ_H

#include "iostream"

using namespace std;

struct response {
    bool success;
    double result;
};

class stack {
private:
    double *values;
    unsigned int currentSize;
    int capacity;

public:
    bool push(double value) {
        if (isFull()) {
            cout << "Нельзя добавить значение в стек: он полон" << endl;
            return false;
        }

        values[currentSize] = value;
        currentSize++;

        return true;
    }

    bool pop(double &value) {
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

    double getTopElement() {
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

    stack(const int cap) {
        values = new double[cap];
        capacity = cap;
        currentSize = 0;
    }
};

bool validateOpzArray(const char **, const int);

void calculate(stack *, const char **, const int, response &, double);
bool isNumber(const char *);
void printResponse(response);

#endif //LAB_5_CALCULATE_OPZ_H
