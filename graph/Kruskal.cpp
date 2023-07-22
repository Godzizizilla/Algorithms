#include <iostream>
#include <vector>
#include <algorithm>

// 定义边的结构体，包含起点、终点和权重
struct Edge {
    int src, dest, weight;
};

// 定义并查集，用于检测环路
class UnionFind {
private:
    std::vector<int> parent;
public:
    UnionFind(int n) : parent(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find(parent[v]);
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            parent[rootU] = rootV;
        }
    }
};

// Kruskal算法实现
std::vector<Edge> kruskalMST(std::vector<Edge>& edges, int numVertices) {
    std::vector<Edge> minimumSpanningTree;
    // 对边按权重进行排序
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    UnionFind uf(numVertices);

    for (const Edge& edge : edges) {
        if (uf.find(edge.src) != uf.find(edge.dest)) {
            // 边不会形成环路，将其加入到最小生成树中
            minimumSpanningTree.push_back(edge);
            uf.unite(edge.src, edge.dest);
        }
    }

    return minimumSpanningTree;
}

int main() {
    int numVertices = 6;
    std::vector<Edge> edges = {
            {0, 1, 4}, {0, 2, 3}, {1, 2, 2}, {1, 3, 1}, {2, 3, 4}, {3, 4, 2}, {4, 5, 6}
    };

    std::vector<Edge> minimumSpanningTree = kruskalMST(edges, numVertices);

    std::cout << "Minimum Spanning Tree:" << std::endl;
    for (const Edge& edge : minimumSpanningTree) {
        std::cout << edge.src << " - " << edge.dest << " : " << edge.weight << std::endl;
    }

    return 0;
}
