#pragma once

#include <utility>
#include <list>
#include <vector>
#include <queue>
#include <unordered_map>

template<typename EdgeValue = int, typename Node = int>
struct Graph {

    using Nodes = std::vector<Node>;
    using ToEdge = std::pair<Node, EdgeValue>;
    using ToEdges = std::vector<ToEdge>;

    std::unordered_set<Node> allNodes;
    void markNode(Node node) { allNodes.insert(node); }
    size_t getNodesNumber() { return allNodes.size(); }

    virtual void addEdge(Node a, Node b, EdgeValue value) = 0;
    virtual ToEdges getToEdge(Node id) = 0;
    virtual Nodes getNeighborsNode(Node id) = 0;

    bool BFS(Node start, Node end, Nodes& nodes) {
        std::unordered_map<Node, Node> parent;
        std::queue<Node> queue;
        queue.push(start);
        std::unordered_set<Node> visited;
        visited.insert(start);

        std::list<Node> nodeList;

        while (!queue.empty()) {
            Node node = queue.front(); queue.pop();

            ToEdges edges = getToEdge(node);
            for (const ToEdge& edge : edges) {
                Node other = edge.first;
                EdgeValue value = edge.second;
                if (!(visited.count(other) == 0 && value > 0)) continue;

                parent.insert({ other, node });
                if (other != end) {
                    queue.push(other);
                    visited.insert(other);
                    continue;
                }

                // Find target //
                Node current = end;
                Node parentNode = parent[end];
                while (current != start) {
                    nodeList.push_front(current);
                    current = parentNode;
                    parentNode = parent[current];
                }
                nodeList.push_front(start);
                nodes = Nodes(nodeList.begin(), nodeList.end());
                return true;
            }
        }

        return false;
    }

    void printAllEdge() {
        std::cout << '\n';
        for (const Node& node : allNodes) {
            ToEdges toEdges = getToEdge(node);
            for (const ToEdge& toEdge : toEdges) {
                Node other = toEdge.first;
                EdgeValue value = toEdge.second;
                std::cout << node << " to " << other << " weight " << value << '\n';
            }
            std::cout << '\n';
        }
    }

    void printAllNeighborsNode() {
        std::cout << '\n';
        for (const Node& node : allNodes) {
            Nodes neighborsNode = getNeighborsNode(node);
            std::cout << node << ": ";
            for (const Node& neighbor : neighborsNode) {
                std::cout << neighbor << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

};



