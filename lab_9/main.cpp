#include "avl.h"

using namespace std;

void secondMenu(AVL b);

int main() {

    AVL b;
    int command = -1, node, height;

    while (command != 0) {
        cout<<endl << "Возможные команды:" << endl;
        cout << "1 - Добавление узла" << endl;
        cout << "2 - Поиск узла по значению" << endl;
        cout << "3 - Определение высоты текущего поддерева" << endl;
        cout << "4 - Вызов меню обхода" << endl;
        cout << "5 - Проверка баланса поддеревьев" << endl;
        cout << "0 - Выход из программы" << endl;
        cout << "Ввод: ";

        cin >> command;

        switch (command) {
            case 1:
                cout << "Введите значение узла (целое число)" << endl;
                cin >> node;
                b.root = b.insert(b.root, node);
                break;
            case 2:
                cout << "Введите значение узла (целое число)" << endl;
                cin >> node;
                b.search_node(node);
                break;
            case 3:
                height = b.get_current_height(b.root);
                cout << "Высота текущего дерева: " << height << endl;
                break;
            case 4:
                secondMenu(b);
                break;
            case 5:
                cout<<"Баланс поддеревьев равен "<<b.getBalance(b.root)<<endl;
                break;
            case 0:
                break;
        }
    }
}
1
void secondMenu(AVL b) {
    int command = -1;
    int height;

    b.current=b.root;

    while (command != 0) {
        cout <<endl<< "Возможные команды меню обхода:" << endl;
        cout << "1 - Печать данных текущего узла" << endl;
        cout << "2 - Переход на левого потомка" << endl;
        cout << "3 - Переход на правого потомка" << endl;
        cout << "4 - Возврат в корень дерева" << endl;
        cout << "5 - Определение высоты текущего поддерева" << endl;
        cout << "6 - Проверка баланса поддеревьев текущего узла" << endl;
        cout << "0 - Выход из режима обхода во внешнее меню" << endl;
        cout << "Ввод: ";

        cin >> command;

        switch (command) {
            case 1:
                b.print_current_node();
                break;
            case 2:
                b.current=b.next_node("left");
                break;
            case 3:
                b.current=b.next_node("right");
                break;
            case 4:
                b.current=b.root;
                cout<<"Переход в корень осуществлён успешно"<<endl;
                break;
            case 5:
                height = b.get_current_height(b.current);
                cout << "Высота текущего дерева: " << height << endl;
                break;
            case 6:
                cout<<"Баланс поддеревьев равен "<<b.getBalance(b.current)<<endl;
                break;
            case 0:
                break;
        }
    }
}