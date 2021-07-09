#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "DistjointSet.h"
#include "UndirectedGraph.h"

template<typename EdgeValue = int, typename Node = int>
struct MinimumSpanningTree {

    using _UndirectedGraph = UndirectedGraph<EdgeValue, Node>;
    using TwoNode = typename _UndirectedGraph::TwoNode;
    using ToEdge  = typename _UndirectedGraph::ToEdge;
    using Edge    = typename _UndirectedGraph::Edge;
    using Edges   = typename _UndirectedGraph::Edges;

    static Edges getMinimumSpanningTreeEdge(_UndirectedGraph graph) {
        Edges allEdge = graph.edges;
        std::sort(allEdge.begin(), allEdge.end(),
            [](const Edge a, const Edge b) {
                return a.second < b.second;
            });
        Edges minimumSpanningTreeEdge;
        DistjointSet disjointSet;
        for (const Edge& edge : allEdge) {
            int nodeA = edge.first.first;
            int nodeB = edge.first.second;
            if (disjointSet.findParent(nodeA) == disjointSet.findParent(nodeB)) continue;
            disjointSet.unionSet(nodeA, nodeB);
            minimumSpanningTreeEdge.push_back(edge);
        }
        return minimumSpanningTreeEdge;
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

        Edges minimumSpanningTreeEdge = MinimumSpanningTree::getMinimumSpanningTreeEdge(graph);
        int total = 0;

        std::cout << "Minimum Spanning Tree Edge:\n";
        for (const Edge& edge : minimumSpanningTreeEdge) {
            TwoNode twoNode = edge.first;
            Node a          = twoNode.first;
            Node b          = twoNode.second;
            EdgeValue value = edge.second;
            std::cout << a << " to " << b << " weight " << value << '\n';
            total += value;
        }
        std::cout << "Total weight: " << total << '\n';
    }

};


