#include <iostream>

using namespace std;
int main() {
    int array[] ={16,2,254,546,1,436,6,75,2};

    int arr_size=sizeof (array)/ sizeof (int);
    sort(array, array+arr_size);

    cout<<"Массив отсортирован: ";

    for (int i = 0; i < arr_size; ++i) {
        cout<<array[i]<<" ";
    }

    cout<<endl;

    int search_el;
    cout<<"Введите искомое число: ";
    cin>>search_el;

    int left=0, right=arr_size-1;
    int mid;

    while (left<=right){
        mid = (right+left)/2;
        if (array[mid]==search_el){
            cout<<"Искомый элемент в массиве находится под индексом "<< mid<<endl;
            return 0;
        }

        if (mid>search_el){
            right=mid-1;
        }else{
            left=mid+1;
        }
    }

    cout<<"Элемент не найден в массиве"<<endl;

    return 0;
}
