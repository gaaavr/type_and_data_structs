#include <iostream>
#include "int32.h"


int main() {
    cout<<"Введите значение первого числа в формате int32: ";
    int32_t value_1;
    cin>>value_1;
    cout<<"Введите значение второго числа в формате int32: ";
    int32_t value_2;
    cin>>value_2;

    Int32 val_1 = Int32(value_1);
    Int32 val_2 = Int32(value_2);

    cout<<"[СЛОЖЕНИЕ]: "<<val_1+val_2<<endl;
    cout<<"[ВЫЧИТАНИЕ]: "<<val_1-val_2<<endl;
    cout<<"[УМНОЖЕНИЕ]: "<<val_1*val_2<<endl;
    cout<<"[СРАВНЕНИЕ >]: "<<(val_1>val_2)<<endl;
    cout<<"[СРАВНЕНИЕ <]: "<<(val_1<val_2)<<endl;
    cout<<"[СРАВНЕНИЕ >=]: "<<(val_1>=val_2)<<endl;
    cout<<"[СРАВНЕНИЕ <=]: "<<(val_1<=val_2)<<endl;
    cout<<"[СРАВНЕНИЕ ==]: "<<(val_1==val_2)<<endl;
    cout<<"[СРАВНЕНИЕ !=]: "<<(val_1!=val_2)<<endl;
    val_1=val_2;
    cout<<"[ПРИСВАИВАНИЕ]: "<<val_1<<" "<<val_2<<endl;

    return 0;
}
