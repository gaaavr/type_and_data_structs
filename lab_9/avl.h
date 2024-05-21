#include <iostream>
#include <queue>

using namespace std;
#ifndef LAB_9_AVL_H
#define LAB_9_AVL_H

struct node {
    struct node *left;
    int data;
    int height;
    struct node *right;
};

class AVL {
public:
    struct node *root;
    struct node *current;

    AVL() {
        root = NULL;
        current = NULL;
    }

    int height(struct node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(struct node *node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    struct node *right_rotate(struct node *n) {
        struct node *tp;
        tp = n->left;

        n->left = tp->right;
        tp->right = n;

        n->height = max(height(n->left), height(n->right)) + 1;
        tp->height = max(height(tp->left), height(tp->right)) + 1;

        return tp;
    }


    struct node *left_rotate(struct node *n) {
        struct node *tp;
        tp = n->right;

        n->right = tp->left;
        tp->left = n;

        n->height = max(height(n->left), height(n->right)) + 1;
        tp->height = max(height(tp->left), height(tp->right)) + 1;

        return tp;
    }


    struct node *big_left_rotate(struct node *n) {
        n->right = right_rotate(n->right);

        return left_rotate(n);
    }

    struct node *big_right_rotate(struct node *n) {
        n->left = left_rotate(n->left);

        return right_rotate(n);
    }

    struct node *insert(struct node *r, int data) {
        if (!r) {
            struct node *n;
            n = new struct node;
            n->data = data;
            r = n;
            r->left = NULL;
            r->right = NULL;
            r->height = 1;
            return r;
        }

        if (data < r->data) {
            r->left = insert(r->left, data);
        } else {
            r->right = insert(r->right, data);
        }

        r->height = 1 + max(height(r->left), height(r->right));

        int balance = getBalance(r);

        if (balance > 1 && data < r->left->data) {
            return right_rotate(r);
        }

        if (balance < -1 && data > r->right->data) {
            return left_rotate(r);
        }

        if (balance > 1 && data > r->left->data) {
            return big_right_rotate(r);
        }

        if (balance < -1 && data < r->right->data) {
            return big_left_rotate(r);
        }

        return r;
    }

    void print_current_node() {
        if (!current) {
            cout << "В дереве нет узлов" << endl;
            return;
        }

        cout << "Значение в текущем узле: " << current->data << endl;
        if (!current->left) {
            cout << "Левая ветвь пустая" << endl;
        } else {
            cout << "Значение в левом узле: " << current->left->data << endl;
        }

        if (!current->right) {
            cout << "Правая ветвь пустая" << endl;
        } else {
            cout << "Значение в правом узле: " << current->right->data << endl;
        }
    }

    struct node *next_node(char *direction) {
        if (!current) {
            cout << "В дереве нет узлов" << endl;
            return current;
        }

        if (direction == "left") {
            if (!current->left) {
                cout << "Левый узел пустой" << endl;
                return current;
            }

            return current->left;
        }

        if (direction == "right") {
            if (!current->right) {
                cout << "Правый узел пустой" << endl;
                return current;
            }

            return current->right;
        }

        cout << "Неизвестное направление для перехода" << endl;

        return current;
    }

    int get_current_height(struct node *r) {
        if (!r) {
            return 0;
        }

        int left, right;
        if (r->left) {
            left = get_current_height(r->left);
        } else {
            left = -1;
        }

        if (r->right) {
            right = get_current_height(r->right);
        } else {
            right = -1;
        }

        int max = left > right ? left : right;

        return max + 1;
    }

    void search_node(int key) {
        int counter = 0;
        if (!root) {
            cout << "В дереве нет таких узлов" << endl;
            return;
        }

        struct node *curNode = root;

        for (;;) {
            if (key == curNode->data) {
                cout << "Узел со значением " << key << " найден на высоте " << counter << endl;
                return;
            }

            if (key > curNode->data) {
                if (!curNode->right) {
                    cout << "Узел со значением " << key << " в дереве не найден" << endl;
                    return;
                }

                curNode = curNode->right;
            } else if (key < curNode->data) {
                if (!curNode->left) {
                    cout << "Узел со значением " << key << " в дереве не найден" << endl;
                    return;
                }

                curNode = curNode->left;
            }

            counter++;
        }
    }
};

#endif //LAB_9_AVL_H
