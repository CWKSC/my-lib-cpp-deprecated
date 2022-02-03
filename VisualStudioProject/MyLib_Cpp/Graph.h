#pragma once

#include <utility>
#include <list>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>

#include <unordered_map>
#include <tuple>




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

    Nodes BFS(Node start) {
        Nodes BFSnodes = { start };

        std::queue<Node> queue;
        std::unordered_set<Node> visited;

        queue.push(start);

        while (!queue.empty()) {
            Node node = queue.front(); queue.pop();

            Nodes neighborsNode = getNeighborsNode(node);
            for (const Node& neighbor : neighborsNode) {
                if (visited.count(neighbor) != 0) continue;
                queue.push(neighbor);
                BFSnodes.push_back(neighbor);
                visited.insert(neighbor);
            }
        }

        return BFSnodes;
    }

    void BFS_Layer(Node start, std::function<void(Nodes, int)> getLayerNodes) {
        std::queue<Node> queue;
        std::unordered_set<Node> visited;

        queue.push(start);

        int index = 0;
        while (!queue.empty()) {

            Nodes layerNodes;
            while (!queue.empty()) {
                layerNodes.push_back(queue.front());
                queue.pop();
            }
            getLayerNodes(layerNodes, index);

            for (const Node& node : layerNodes) {
                Nodes neighborsNode = getNeighborsNode(node);
                for (const Node& neighbor : neighborsNode) {
                    if (visited.count(neighbor) != 0) continue;
                    queue.push(neighbor);
                    visited.insert(neighbor);
                }
            }

            index++;
        }
    }


    Nodes DFS(Node start) {
        Nodes DFSnodes;
        std::unordered_set<Node> visited;
        DFS_visit(start, DFSnodes, visited);
        return DFSnodes;
    }
    void DFS_visit(Node node, Nodes& DFSnodes, std::unordered_set<Node>& visited) {
        DFSnodes.push_back(node);
        visited.insert(node);
        Nodes neighborsNode = getNeighborsNode(node);
        for (const Node& neighbor : neighborsNode) {
            if (visited.count(neighbor) != 0) continue;
            DFS_visit(neighbor, DFSnodes, visited);
        }
    }


    bool GetNodesStartToEndByBFS(Node start, Node end, Nodes& nodes) {
        std::unordered_map<Node, Node> parent;
        std::queue<Node> queue;
        std::unordered_set<Node> visited;
        std::list<Node> nodeList;

        queue.push(start);
        visited.insert(start);

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

    static void printNodes(Nodes nodes) {
        for (Node node : nodes) {
            std::cout << node << " ";
        }
    }

};




namespace GraphAlgoritm {

    template <typename Node, typename Value>
    std::vector<std::tuple<Node, Node, Value>> getAllEdge(const std::unordered_map<Node, std::unordered_map<Node, Value>>& graph) {
        std::vector<std::tuple<Node, Node, Value>> edges;
        for (const std::pair<Node, std::unordered_map<Node, Value>>& fromTo : graph) {
            Node from = fromTo.first;
            std::unordered_map<Node, Value> toEdges = fromTo.second;
            for (const std::pair<Node, Value>& toEdge : toEdges) {
                Node to = toEdge.first;
                Value length = toEdge.second;
                edges.push_back(std::make_tuple(from, to, length));
            }
        }
        return edges;
    }
}


