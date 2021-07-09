#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <vector>
#include <queue>

#include "DistjointSet.h"
#include "Graph.h"

template<typename EdgeValue = int, typename Node = int>
struct UndirectedGraph : public Graph<EdgeValue, Node> {

    using Nodes = std::vector<Node>;
    using TwoNode = std::pair<Node, Node>;
    using ToEdge = std::pair<Node, EdgeValue>;
    using ToEdges = std::vector<ToEdge>;
    using Edge = std::pair<TwoNode, EdgeValue>;
    using Edges = std::vector<Edge>;

    Edges edges;

    UndirectedGraph() {}
    UndirectedGraph(Edges edges) {
        this->edges = edges;
        for (const Edge& edge : edges) {
            TwoNode twoNode = edge.first;
            this->markNode(twoNode.first);
            this->markNode(twoNode.second);
        }
    }

    void addEdge(Node a, Node b, EdgeValue value) override {
        bool finded = false;
        for (Edge& edge : edges) {
            if (edge.first.first == a && edge.first.second == b ||
                edge.first.first == b && edge.first.second == a) {
                finded = true;
                edge.second += value;
            }
        }
        if (finded == false) {
            edges.push_back({ { a, b }, value });
        }
        this->markNode(a);
        this->markNode(b);
    }

    ToEdges getToEdge(Node id) override {
        ToEdges v;
        for (const Edge& edge : edges) {
            TwoNode twoNode = edge.first;
            if (twoNode.first == id) {
                v.push_back({ twoNode.second, edge.second });
            }
            else if (twoNode.second == id) {
                v.push_back({ twoNode.first, edge.second });
            }
        }
        return v;
    }

    Nodes getNeighborsNode(Node id) override {
        Nodes v;
        for (const Edge& edge : edges) {
            TwoNode twoNode = edge.first;
            if (twoNode.first == id) {
                v.push_back(twoNode.second);
            }
            else if (twoNode.second == id) {
                v.push_back(twoNode.first);
            }
        }
        return v;
    }

    static void test() {
        UndirectedGraph<> graph;
        graph.addEdge(0, 1, 5);
        graph.addEdge(0, 3, 3);
        graph.addEdge(3, 6, 5);
        graph.addEdge(6, 7, 3);
        graph.addEdge(7, 5, 1);
        graph.addEdge(7, 8, 4);
        graph.addEdge(0, 5, 1);
        graph.addEdge(5, 4, 0);
        graph.addEdge(1, 4, -3);
        graph.addEdge(4, 2, -1);
        graph.addEdge(4, 8, 5);
        graph.addEdge(8, 8, 2);
        graph.addEdge(5, 8, 2);

        graph.printAllEdge();
        graph.printAllNeighborsNode();
    }

};




