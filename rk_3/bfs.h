//
// Created by ssgavrilin on 28.04.2024.
//

#ifndef RK_3_BFS_H
#define RK_3_BFS_H

#include <vector>
#include <map>
#include "queue.h"
#include <iostream>

using namespace std;

struct Graph {
    vector<vector<int>> matrix;
    map<int, string> indexToStrMap; // мапа для преобразования индекса матрицы в строковое значение узла графа
};

Graph *createGraph() {
    // Матрица смежности неориентированного графа
    vector<vector<int>> adjMatrix = {
          // А  Б  В  Г  Е  Ф  Ж  З  К  Л  И  М
            {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // А
            {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, // Б
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // В
            {0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, // Г
            {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // Е
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // Ф
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // Ж
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}, // З
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // К
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1}, // Л
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // И
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // М
    };

    map<int, string> indexToStr = {
            {0,  "А"},
            {1,  "Б"},
            {2,  "В"},
            {3,  "Г"},
            {4,  "Е"},
            {5,  "Ф"},
            {6,  "Ж"},
            {7,  "З"},
            {8,  "К"},
            {9,  "Л"},
            {10, "И"},
            {11, "М"},
    };

    Graph * g = new Graph;

    g->matrix=adjMatrix;
    g->indexToStrMap=indexToStr;
    return g;
}

int searchNode(Graph *graph, string nodeMarker) {
    for (int i = 0; i < graph->matrix.size(); i++) {
        if (graph->indexToStrMap.find(i)->second == nodeMarker) {
            return i;
        }
    }

    return -1;
}

// Функция BFS для обхода графа в ширину
void BFS(queue *q, vector<string> &visitedNodes, Graph *graph) {
    while (!q->isEmpty()) {
        int curNode;

        if (!q->pop(curNode)) {
            cout << "Ошибка при попытке достать узел из очереди" << endl;
            exit(1);
        };

        string strMarker = graph->indexToStrMap.find(curNode)->second;

        cout << strMarker << " ";

        for (int i = 0; i < graph->matrix.size(); i++) {
            string nextStrMarker = graph->indexToStrMap.find(i)->second;
            if (nodeIsVisited(nextStrMarker, visitedNodes) || graph->matrix[curNode][i]==0) {
                continue;
            }

            if (!q->push(i)) {
                cout << "Ошибка при попытке поместить узел в стек" << endl;
                exit(1);
            }

            visitedNodes.push_back(graph->indexToStrMap.find(i)->second);
        }
    }
}

#endif //RK_3_BFS_H
