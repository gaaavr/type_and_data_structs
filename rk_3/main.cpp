#include <iostream>
#include "stack.h"
#include "dfs.h"
#include "bfs.h"
#include <vector>

using namespace std;

int main() {
    // Обход в глубину ор графа
    Node *orGraphHead = createOrGraph();

    string curNodeMarker;
    cout << "Введите метку узла, с которого хотите начать обход в глубину: ";
    cin >> curNodeMarker;

    Node *curNode = searchNodeOrGraph(orGraphHead, curNodeMarker);
    if (!curNode) {
        cout << "Узел с такой меткой не найден";
        return 0;
    }

    stack *st = new stack(12);
    if (!st->push(curNode)) {
        cout << "Ошибка при попытке поместить узел в стек" << endl;
        return 1;
    };

    vector<string> visitedNodes;
    visitedNodes.push_back(curNode->data);

    cout << "Результат обхода в глубину: ";
    DFS(st, visitedNodes);

    st->free();
    visitedNodes.clear();

    // Обход в ширину неорграфа
    Graph *graph = createGraph();

    cout << endl << "Введите метку узла, с которого хотите начать обход в ширину: ";
    cin >> curNodeMarker;

    int curIntNode = searchNode(graph, curNodeMarker);
    if (curIntNode==-1) {
        cout << "Узел с такой меткой не найден";
        return 0;
    }

    queue *q = new queue(12);
    if (!q->push(curIntNode)) {
        cout << "Ошибка при попытке поместить узел в очередь" << endl;
        return 1;
    };

    visitedNodes.push_back( graph->indexToStrMap.find(curIntNode)->second);

    cout << "Результат обхода в ширину: ";
    BFS(q, visitedNodes, graph);

    q->free();
    visitedNodes.clear();

    return 0;
}
