#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

/* Disjoint Set (Union-Find) for Kruskal’s MST */
class DisjointSet {
private:
    vector<int> parent, rank;
public:
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findSet(int v) {
        if (v == parent[v]) return v;
        return parent[v] = findSet(parent[v]); // Path compression
    }

    bool unionSet(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

/* WeightedGraph class: Adjacency List + Algorithms */
class WeightedGraph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjList;

public:
    WeightedGraph(int n) : numVertices(n), adjList(n) {}

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    void printGraph() {
        cout << "Graph structure (Adjacency List):" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ":";
            for (auto &edge : adjList[i]) {
                cout << " -> (" << edge.first << ", w=" << edge.second << ")";
            }
            cout << endl;
        }
        cout << endl;
    }

    int primsMST(int start) {
        vector<bool> inMST(numVertices, false);
        vector<int> key(numVertices, INT_MAX);
        vector<int> parent(numVertices, -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        key[start] = 0;
        minHeap.push({0, start});
        int totalCost = 0;

        while (!minHeap.empty()) {
            int u = minHeap.top().second;
            int weight = minHeap.top().first;
            minHeap.pop();

            if (inMST[u]) continue;
            inMST[u] = true;
            totalCost += weight;

            for (auto &edge : adjList[u]) {
                int v = edge.first, w = edge.second;
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    minHeap.push({w, v});
                }
            }
        }

        cout << "Prim’s MST edges:" << endl;
        for (int v = 0; v < numVertices; v++) {
            if (parent[v] != -1)
                cout << parent[v] << " -- " << v << "  (weight " << key[v] << ")" << endl;
        }
        cout << "Total MST Cost (Prim’s) = " << totalCost << endl << endl;
        return totalCost;
    }

    int kruskalMST() {
        vector<tuple<int, int, int>> edges;
        for (int u = 0; u < numVertices; u++) {
            for (auto &edge : adjList[u]) {
                int v = edge.first, w = edge.second;
                if (v > u) edges.emplace_back(w, u, v);
            }
        }

        sort(edges.begin(), edges.end());
        DisjointSet ds(numVertices);
        int totalCost = 0;

        cout << "Kruskal’s MST edges:" << endl;
        for (auto &[w, u, v] : edges) {
            if (ds.unionSet(u, v)) {
                cout << u << " -- " << v << "  (weight " << w << ")" << endl;
                totalCost += w;
            }
        }
        cout << "Total MST Cost (Kruskal’s) = " << totalCost << endl << endl;
        return totalCost;
    }

    void dijkstra(int start) {
        vector<int> dist(numVertices, INT_MAX);
        vector<bool> visited(numVertices, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (auto &edge : adjList[u]) {
                int v = edge.first, w = edge.second;
                if (!visited[v] && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Dijkstra’s shortest paths from vertex " << start << ":\n";
        for (int i = 0; i < numVertices; i++) {
            if (dist[i] == INT_MAX)
                cout << "Vertex " << i << ": unreachable\n";
            else
                cout << "Vertex " << i << ": " << dist[i] << "\n";
        }
        cout << endl;
    }
};

int main() {
    WeightedGraph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);

    g.printGraph();
    g.primsMST(0);
    g.kruskalMST();
    g.dijkstra(0);

    return 0;
}