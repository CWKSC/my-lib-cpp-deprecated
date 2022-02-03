#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "DistjointSet.h"
#include "UndirectedGraph.h"

//template<typename EdgeValue = int, typename Node = int>
//struct MinimumSpanningTree {
//
//    using _UndirectedGraph = UndirectedGraph<EdgeValue, Node>;
//    using TwoNode = typename _UndirectedGraph::TwoNode;
//    using ToEdge  = typename _UndirectedGraph::ToEdge;
//    using Edge    = typename _UndirectedGraph::Edge;
//    using Edges   = typename _UndirectedGraph::Edges;
//
//    static Edges getMinimumSpanningTreeEdge(_UndirectedGraph graph) {
//        Edges allEdge = graph.edges;
//        std::sort(allEdge.begin(), allEdge.end(),
//            [](const Edge a, const Edge b) {
//                return a.second < b.second;
//            });
//        Edges minimumSpanningTreeEdge{};
//        DistjointSet disjointSet;
//        for (const Edge& edge : allEdge) {
//            int nodeA = edge.first.first;
//            int nodeB = edge.first.second;
//            if (disjointSet.findParent(nodeA) == disjointSet.findParent(nodeB)) continue;
//            disjointSet.unionSet(nodeA, nodeB);
//            minimumSpanningTreeEdge.push_back(edge);
//        }
//        return minimumSpanningTreeEdge;
//    }
//
//    static void test() {
//        UndirectedGraph<> graph;
//        graph.addEdge(0, 1, 5);
//        graph.addEdge(0, 3, 3);
//        graph.addEdge(3, 6, 5);
//        graph.addEdge(6, 7, 3);
//        graph.addEdge(7, 5, 1);
//        graph.addEdge(7, 8, 4);
//        graph.addEdge(0, 5, 1);
//        graph.addEdge(5, 4, 0);
//        graph.addEdge(1, 4, -3);
//        graph.addEdge(4, 2, -1);
//        graph.addEdge(4, 8, 5);
//        graph.addEdge(8, 8, 2);
//        graph.addEdge(5, 8, 2);
//
//        graph.printAllEdge();
//        graph.printAllNeighborsNode();
//
//        Edges minimumSpanningTreeEdge = MinimumSpanningTree::getMinimumSpanningTreeEdge(graph);
//        int total = 0;
//
//        std::cout << "Minimum Spanning Tree Edge:\n";
//        for (const Edge& edge : minimumSpanningTreeEdge) {
//            TwoNode twoNode = edge.first;
//            Node a          = twoNode.first;
//            Node b          = twoNode.second;
//            EdgeValue value = edge.second;
//            std::cout << a << " to " << b << " weight " << value << '\n';
//            total += value;
//        }
//        std::cout << "Total weight: " << total << '\n';
//    }
//
//};
//


#include <unordered_map>
#include <tuple>

namespace MinimumSpanningTree {

    template <typename Node, typename Value>
    void Kruskals(std::unordered_map<Node, std::unordered_map<Node, Value>>& graph) {
        std::vector<std::tuple<Node, Node, Value>> edges = Graph::getAllEdge(graph);
        std::sort(edges.begin(), edges.end(),
            [](const std::tuple<Node, Node, Value> a, const std::tuple<Node, Node, Value> b) {
                return std::get<2>(a) < std::get<2>(b);
            });
        std::vector<std::tuple<Node, Node, Value>> minimumSpanningTreeEdge;
        std::unordered_map<Node, Node> disjointSet;
        for (const std::tuple<Node, Node, Value>& edge : edges) {
            int nodeA = edge.first;
            int nodeB = edge.second;
            if (DistjointSet::findParent(disjointSet, nodeA) ==
                DistjointSet::findParent(disjointSet, nodeB)) continue;
            DistjointSet::unionSet(disjointSet, nodeA, nodeB);
            minimumSpanningTreeEdge.push_back(edge);
        }
        return;
    }

}


//void UVa395() {
//    std::ios::sync_with_stdio(false);
//    std::cin.tie(nullptr);
//    std::cout.tie(nullptr);
//
//    int n, m;
//    while (std::cin >> n >> m) {
//        if (n == 0 && m == 0) break;
//        std::unordered_map<int, std::unordered_map<int, int>> graph;
//        int a, b, w;
//        for (int i = 0; i < m; i++) {
//            std::cin >> a >> b >> w;
//            graph[a][b] = w;
//        }
//        std::vector<std::tuple<int, int, int>> edges = Graph::getAllEdge(graph);
//        std::sort(edges.begin(), edges.end(),
//            [](const std::tuple<int, int, int> a, const std::tuple<int, int, int> b) {
//                return std::get<2>(a) < std::get<2>(b);
//            });
//        int ans = 0x3f3f3f3f;
//        for (int i = 0; i < m; i++) {
//            DistjointSet disjointSet;
//            int count = 0;
//            int max = 0;
//            int min = 0x3f3f3f3f;
//            for (int j = i; j < m; j++) {
//                std::tuple<int, int, int>& edge = edges[j];
//                if (disjointSet.findParent(std::get<0>(edge)) ==
//                    disjointSet.findParent(std::get<1>(edge))) continue;
//                disjointSet.unionSet(std::get<0>(edge), std::get<1>(edge));
//                count++;
//                max = std::max(max, std::get<2>(edge));
//                min = std::min(min, std::get<2>(edge));
//                if (count == n - 1) {
//                    int diff = max - min;
//                    ans = std::min(ans, diff);
//                }
//            }
//            if (ans == 0) break;
//        }
//        if (ans != 0x3f3f3f3f) {
//            std::cout << ans << std::endl;
//        }
//        else {
//            std::cout << "-1" << std::endl;
//        }
//
//    }
//}
//
