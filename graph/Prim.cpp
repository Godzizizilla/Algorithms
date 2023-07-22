#include <iostream>
#include <vector>
#include <queue>

struct Edge {
    int dest;
    int weight;
};

class UndirectedGraph {
private:
    int numVertices;
    std::vector<std::vector<Edge>> adjList;

public:
    UndirectedGraph(int V) : numVertices(V), adjList(V) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Since it's an undirected graph, add edges in both directions.
    }

    void primMST() {
        std::vector<bool> visited(numVertices, false);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        std::vector<int> miniDist(numVertices, INT_MAX);
        std::vector<int> parent(numVertices, -1);

        // Start with vertex 0 as the starting point
        pq.push(std::make_pair(0, 0));
        miniDist[0] = 0;

        while (!pq.empty()) {
            // 取出权值最小的边 对应的顶点
            int u = pq.top().second;
            pq.pop();

            // 所有的顶点都是未访问的吗?
            if (visited[u])
                continue;

            visited[u] = true;

            // 遍历当前访问顶点的邻顶点
            for (const Edge& edge : adjList[u]) {
                int v = edge.dest;
                int weight = edge.weight;

                // 更新距离
                if (!visited[v] && weight < miniDist[v]) {
                    parent[v] = u;
                    miniDist[v] = weight;
                    pq.push(std::make_pair(miniDist[v], v));
                }
            }
        }

        // Print the minimum spanning tree
        std::cout << "Minimum Spanning Tree:" << std::endl;
        for (int i = 1; i < numVertices; ++i) {
            std::cout << parent[i] << " - " << i << " : " << miniDist[i] << std::endl;
        }
    }
};

int main() {
    UndirectedGraph graph(5);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);

    graph.primMST();

    return 0;
}
