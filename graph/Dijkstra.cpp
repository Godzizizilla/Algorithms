#include <iostream>
#include <vector>
#include <queue>
#include <limits>

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

    void dijkstraShortestPath(int startVertex) {
        std::vector<int> distance(numVertices, INT_MAX);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        distance[startVertex] = 0;
        pq.push(std::make_pair(0, startVertex));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const Edge &edge: adjList[u]) {
                int v = edge.dest;
                int weight = edge.weight;

                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    pq.push(std::make_pair(distance[v], v));
                }
            }
        }

        // Output the shortest distances from startVertex to all other vertices
        std::cout << "Shortest distances from vertex " << startVertex << " to all other vertices:" << std::endl;
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "Vertex " << i << ": " << distance[i] << std::endl;
        }
    }
};

int main() {
    UndirectedGraph graph(6);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);

    graph.dijkstraShortestPath(0);

    return 0;
}
