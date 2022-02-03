#pragma once

#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <utility>

#include "DirectedGraph.h"
#include "UndirectedGraph.h"


template<typename EdgeValue = int, typename Node = int>
struct MaxFlow
{
    using _DirectedGraph   = DirectedGraph<EdgeValue, Node>;
    using _UndirectedGraph = UndirectedGraph<EdgeValue, Node>;

    using Nodes      = typename _DirectedGraph::Nodes;
    using ToEdgesMap = typename _DirectedGraph::ToEdgesMap;
    using ToEdges    = typename _DirectedGraph::ToEdges;
    using ToEdge     = typename _DirectedGraph::ToEdge;
    using Edge       = typename _DirectedGraph::Edge;

    using Path  = std::pair<int, int>;
    using Paths = std::list<Path>;

    static bool findAugmentingPath(Graph<>* graph, int s, int t, Paths& paths) {
        Nodes nodes;
        if (!graph->GetNodesStartToEndByBFS(s, t, nodes)) return false;

        for (size_t i = 0; i < nodes.size() - 1; i++) {
            paths.push_back({ nodes[i], nodes[i + 1] });
        }
        return true;
    }

    static _DirectedGraph getMaxFlowNetwork(_DirectedGraph graph, int s, int t, int& maxFlow) {

        _DirectedGraph residualNetwork(graph.edges);
        maxFlow = 0;

        while (true) {
            Paths paths;
            if (!findAugmentingPath(&residualNetwork, s, t, paths)) break;

            int min = 0x3f3f3f3f;
            for (const Path& startToEnd : paths) {
                min = std::min(min, residualNetwork.edges[startToEnd.first][startToEnd.second]);
            }
            for (const Path& startToEnd : paths) {
                residualNetwork.edges[startToEnd.first][startToEnd.second] -= min;
            }
            maxFlow += min;
        }

        _DirectedGraph maxFlowNetwork(graph.edges);
        for (const Edge& edge : residualNetwork.edges) {
            for (const ToEdge& toEdge : edge.second) {
                maxFlowNetwork.edges[edge.first][toEdge.first] -= toEdge.second;
            }
        }

        return maxFlowNetwork;
    }


    static _DirectedGraph getMaxFlowNetwork(_UndirectedGraph graph, int s, int t, int& maxFlow) {

        _DirectedGraph residualNetwork(graph);
        maxFlow = 0;

        while (true) {
            Paths paths;
            if (!findAugmentingPath(&residualNetwork, s, t, paths)) break;

            int min = 0x3f3f3f3f;
            for (const Path& startToEnd : paths) {
                min = std::min(min, residualNetwork.edges[startToEnd.first][startToEnd.second]);
            }
            for (const Path& startToEnd : paths) {
                residualNetwork.edges[startToEnd.first][startToEnd.second] -= min;
                residualNetwork.edges[startToEnd.second][startToEnd.first] += min;
            }
            maxFlow += min;
        }

        _DirectedGraph maxFlowNetwork(graph.edges);
        for (const Edge& edge : residualNetwork.edges) {
            for (const ToEdge& toEdge : edge.second) {
                maxFlowNetwork.edges[edge.first][toEdge.first] -= toEdge.second;
            }
        }

        return maxFlowNetwork;
    }


    static void test() {
        _DirectedGraph graph;
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

        int maxFlow = 0;
        _DirectedGraph maxFlowNetwork = getMaxFlowNetwork(graph, 0, 5, maxFlow);

        std::cout << "maxFlow: " << maxFlow << '\n';
        maxFlowNetwork.printAllEdge();
    }

    static void test2() {
        _DirectedGraph graph;
        graph.addEdge(0, 2, 10);
        graph.addEdge(0, 3, 10);
        graph.addEdge(2, 3, 2);
        graph.addEdge(2, 4, 4);
        graph.addEdge(2, 5, 8);
        graph.addEdge(3, 5, 9);
        graph.addEdge(4, 6, 10);
        graph.addEdge(5, 4, 6);
        graph.addEdge(5, 6, 10);

        graph.printAllEdge();
        graph.printAllNeighborsNode();

        int maxFlow = 0;
        _DirectedGraph maxFlowNetwork = getMaxFlowNetwork(graph, 0, 6, maxFlow);

        std::cout << "maxFlow: " << maxFlow << '\n';
        maxFlowNetwork.printAllEdge();
    }

    static void UVa820() {

        int index = 1;
        while (true) {

            int n;
            int s, t, c;
            int nodeA, nodeB, value;
            _UndirectedGraph graph;

            std::cin >> n;
            if (n == 0) break;
            std::cin >> s >> t >> c;
            for (int i = 0; i < c; i++) {
                std::cin >> nodeA >> nodeB >> value;
                graph.addEdge(nodeA, nodeB, value);
            }

            int maxFlow = 0;
            _DirectedGraph maxFlowNetwork = getMaxFlowNetwork(graph, s, t, maxFlow);

            std::cout << "Network " << index << '\n';
            index++;
            std::cout << "The bandwidth is " << maxFlow << ".\n\n";
        }
    }

    static void UVa10092() {

        while (true) {
            int nk, np;
            int numberOfCategory;
            int category;
            _DirectedGraph graph;

            std::cin >> nk >> np;
            if (nk == 0 && np == 0) break;
            std::vector<int> questionNumber(nk);
            int endNode = 0;
            int startNode = nk + np;
            int sumQuestion = 0;
            for (int i = 0; i < nk; i++) {
                std::cin >> questionNumber[i];
                graph.addEdge(1 + i, endNode, questionNumber[i]);
                sumQuestion += questionNumber[i];
            }
            for (int i = 0; i < np; i++) {
                std::cin >> numberOfCategory;
                for (int j = 0; j < numberOfCategory; j++) {
                    std::cin >> category;
                    graph.addEdge(nk + i, category, 1);
                }
                graph.addEdge(startNode, nk + i, 1);
            }

            int maxFlow = 0;
            _DirectedGraph maxFlowNetwork = getMaxFlowNetwork(graph, startNode, 0, maxFlow);
            std::cout << (maxFlow == sumQuestion) << "\n";
        }

    }

};

