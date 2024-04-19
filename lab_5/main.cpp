#include <iostream>
#include "calculate_opz.h"
#include "funcs_table.h"
#include "infix_to_postfix.h"
#include "queue.h"

const int size_infix =3;

/* const char *infix[] = {"0", "-", "(","0","-", "10", ")","+","20", "*","30",
                           "-", "40", "^", "(", "5", "-", "x", "*", "6",
                           "^", "(", "0", "-", "7", ")", ")"}; */
/* const char *infix[] = {"0","-", "90", "+", "9", "-", "8", "^", "(",
                           "1","-", "(", "0","-","2",")","+","4","^",
                           "(","0", "-","1",")","*","3","-","1",")","/",
                           "(","0","-","4","^","(","1","/","2",")","+","1",")"} */

int main() {
    queue *q= new queue(5);

    q->push(1);
    q->push(2);
    q->push(3);
    q->push(4);
    q->push(5);

    int value;
    q->pop(value);
    q->pop(value);

    q->display();
    q->push(6);
    q->push(7);

    q->display();
    q->push(7);
    q->push(7);
    q->display();
    q->push(7);
    q->push(7);
    q->display();
    q->pop(value);
    q->pop(value);
    q->push(7);
    q->push(7);
    q->push(7);
    q->push(7);
    q->display();
    q->pop(value);
    q->push(7);
    q->display();
    q->pop(value);
    q->pop(value);
    q->pop(value);
    q->pop(value);
    q->display();
    q->pop(value);
    q->display();
    exit(0);

    response_infix ri = {
            .success=false,
            .result=0,
            .result_size=0,
    };

    const char *infix[] = {"1", "/", "x"};
    convertInfixToPostfix(infix, size_infix, ri);
    if (!ri.success) {
        cout << "Не удалось перевести выражение из инфиксной записи в постфиксную" << endl;
        return 1;
    }

    printResponseInfix(ri);

    stack *st = new stack(ri.result_size);

    response r = {
            .success=false,
            .result=0,
    };

    if (!validateOpzArray(ri.result, ri.result_size)) {
        printResponse(r);
    };

    double x = 1;
    calculate(st, ri.result,ri.result_size, r, x);

    printResponse(r);

    printFuncTable(ri.result, ri.result_size);

    st->free();

    return 0;
}