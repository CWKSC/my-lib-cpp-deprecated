#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include "Graph.h"
#include "UndirectedGraph.h"


template<typename EdgeValue = int, typename Node = int>
struct DirectedGraph : public Graph<EdgeValue, Node>
{
    using Nodes = std::vector<Node>;
    using ToEdgesMap = std::unordered_map<Node, EdgeValue>;
    using ToEdge = std::pair<Node, EdgeValue>;
    using ToEdges = std::vector<ToEdge>;
    using Edge = std::pair<int, ToEdgesMap>;
    using Edges = std::unordered_map<Node, ToEdgesMap>;

    Edges edges;

    DirectedGraph() {}
    DirectedGraph(Edges edges) {
        this->edges = edges;
        for (Edge edge : edges) {
            this->markNode(edge.first);
            for (ToEdge toEdge : edge.second) {
                this->markNode(toEdge.first);
            }
        }
    }
    using _UndirectedGraph = UndirectedGraph<EdgeValue, Node>;
    DirectedGraph(_UndirectedGraph undirectedGraph) {
        for (const typename _UndirectedGraph::Edge& edge : undirectedGraph.edges) {
            typename _UndirectedGraph::TwoNode twoNode = edge.first;
            addEdge(twoNode.first, twoNode.second, edge.second);
            addEdge(twoNode.second, twoNode.first, edge.second);
        }
    }

    void addEdge(Node a, Node b, EdgeValue value) override {
        if (edges.count(a) == 0) {
            edges.insert({ a, ToEdgesMap() });
        }
        if (edges[a].count(b) == 0) {
            edges[a].insert({ b, value });
        }
        else {
            edges[a][b] = value;
        }
        this->markNode(a);
        this->markNode(b);
    }


    ToEdges getToEdge(Node id) override {
        ToEdges v;
        if (edges.count(id) == 0) return v;

        ToEdgesMap toNodeEdges = edges[id];
        for (const ToEdge& toEdge : toNodeEdges) {
            v.push_back(toEdge);
        }
        return v;
    }

    Nodes getNeighborsNode(Node id) override {
        Nodes v;
        if (edges.count(id) == 0) return v;

        ToEdgesMap toNodeEdges = edges[id];
        for (const ToEdge& toEdge : edges[id]) {
            v.push_back(toEdge.first);
        }
        return v;
    }


    static void test() {
        DirectedGraph<> graph;
        graph.addEdge(0, 1, 16);
        graph.addEdge(0, 2, 13);
        graph.addEdge(1, 3, 12);
        graph.addEdge(1, 2, 10);
        graph.addEdge(2, 1, 4);
        graph.addEdge(2, 4, 14);
        graph.addEdge(3, 2, 9);
        graph.addEdge(3, 5, 20);
        graph.addEdge(4, 3, 7);
        graph.addEdge(4, 5, 4);

        graph.printAllEdge();
        graph.printAllNeighborsNode();
    }


    static void test2() {
        DirectedGraph<> graph;
        graph.addEdge(0, 4, 1);
        graph.addEdge(0, 7, 1);

        graph.addEdge(1, 0, 1);
        graph.addEdge(1, 2, 1);
        graph.addEdge(1, 3, 1);

        graph.addEdge(3, 2, 1);
        graph.addEdge(3, 1, 1);
        graph.addEdge(3, 7, 1);

        graph.addEdge(4, 6, 1);
        graph.addEdge(4, 7, 1);
        
        graph.addEdge(5, 4, 1);

        graph.addEdge(6, 5, 1);

        graph.addEdge(7, 5, 1);

        graph.printAllEdge();
        graph.printAllNeighborsNode();

        std::cout << "BFS: ";
        Nodes BFSnodes = graph.BFS(0);
        Graph<>::printNodes(BFSnodes);
        std::cout << "\n\n";

        std::cout << "BFS Layer: ";
        graph.BFS_Layer(0, [](Nodes nodes, int layer) {
            std::cout << "Layer " << layer << ": ";
            Graph<>::printNodes(nodes);
            std::cout << '\n';
        });
        std::cout << '\n';

        std::cout << "DFS: ";
        Nodes DFSnodes = graph.DFS(0);
        Graph<>::printNodes(DFSnodes);
        std::cout << '\n';

    }

};




