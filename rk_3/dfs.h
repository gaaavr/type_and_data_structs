//
// Created by ssgavrilin on 28.04.2024.
//

#ifndef RK_3_DFS_H
#define RK_3_DFS_H

#include "node.h"
#include "stack.h"

using namespace std;

// Функция для добавления ребра между вершинами
void addEdge(Node *node1, Node *node2) {
    node1->neighbors.push_back(node2);
}

Node *createOrGraph() {
    // Создаем вершины графа
    Node *node1 = new Node("А");
    Node *node2 = new Node("Б");
    Node *node3 = new Node("В");
    Node *node4 = new Node("Г");
    Node *node5 = new Node("Ж");
    Node *node6 = new Node("Ф");
    Node *node7 = new Node("З");
    Node *node8 = new Node("И");
    Node *node9 = new Node("Е");
    Node *node10 = new Node("К");
    Node *node11 = new Node("Л");
    Node *node12 = new Node("М");

    // Добавляем ребра между вершинами
    addEdge(node1, node2);
    addEdge(node1, node3);
    addEdge(node3, node6);
    addEdge(node6, node11);
    addEdge(node11, node12);
    addEdge(node2, node4);
    addEdge(node2, node9);
    addEdge(node4, node5);
    addEdge(node4, node7);
    addEdge(node7, node8);
    addEdge(node9, node10);

    return node1;
}

// Функция DFS для обхода графа в глубину
void DFS(stack *st, vector<string> &visitedNodes) {
    while (!st->isEmpty()) {
        Node *curNode;

        if (!st->pop(curNode)) {
            cout << "Ошибка при попытке достать узел из стека" << endl;
            exit(1);
        };

        cout << curNode->data << " ";

        for (int i = curNode->neighbors.size() - 1; i >= 0; --i) {
            Node *nextNode = curNode->neighbors[i];
            if (nodeIsVisited(nextNode->data, visitedNodes)) {
                continue;
            }

            if (!st->push(nextNode)) {
                cout << "Ошибка при попытке поместить узел в стек" << endl;
                exit(1);
            }

            visitedNodes.push_back(nextNode->data);
        }
    }
}

#endif //RK_3_DFS_H
