#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

class UndirectedGraph {
private:
    int numVertices;
    std::vector<std::list<int>> adjList;

public:
    UndirectedGraph(int V) : numVertices(V), adjList(V) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since it's an undirected graph, add edges in both directions.
    }

    void DFSUtil(int v, std::vector<bool> &visited) {
        visited[v] = true;
        std::cout << v << " ";
        for (const int &neighbor: adjList[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS_Recursive(int startVertex) {
        std::vector<bool> visited(numVertices, false);
        DFSUtil(startVertex, visited);
        std::cout << std::endl;
    }

    void DFS_Non_Recursive(int startVertex) {
        std::vector<bool> visited(numVertices, false);
        std::stack<int> vertexStack;

        vertexStack.push(startVertex);
        visited[startVertex] = true; // 标记起始节点为已访问

        while (!vertexStack.empty()) {
            int v = vertexStack.top();
            vertexStack.pop();
            std::cout << v << " ";

            for (const int &neighbor: adjList[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true; // 标记未访问过的邻居节点为已访问
                    vertexStack.push(neighbor);
                }
            }
        }

        std::cout << std::endl;
    }

    void BFS(int startVertex) {
        std::vector<bool> visited(numVertices, false);
        std::queue<int> vertexQueue;

        vertexQueue.push(startVertex);
        visited[startVertex] = true;

        while (!vertexQueue.empty()) {
            int v = vertexQueue.front();
            vertexQueue.pop();

            std::cout << v << " ";

            for (const auto &neighbor: adjList[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    vertexQueue.push(neighbor);
                }
            }
        }

        std::cout << std::endl;
    }
};

int main() {
    UndirectedGraph graph(5);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    std::cout << "Recursive BFS traversal starting from vertex 0: ";
    graph.BFS(0);

    return 0;
}
