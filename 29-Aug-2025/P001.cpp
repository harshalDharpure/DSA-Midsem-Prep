#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V + 1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }

    // Brute Force: Using Adjacency Matrix
    vector<int> bfsBrute(int start) {
        // Create adjacency matrix
        vector<vector<int>> matrix(V + 1, vector<int>(V + 1, 0));
        for (int u = 1; u <= V; u++) {
            for (auto v : adj[u]) {
                matrix[u][v] = 1;
                matrix[v][u] = 1;
            }
        }

        vector<int> result;
        vector<bool> visited(V + 1, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);

            for (int v = 1; v <= V; v++) {
                if (matrix[node][v] == 1 && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return result;
    }

    // Optimal: Using Adjacency List
    vector<int> bfsOptimal(int start) {
        vector<int> result;
        vector<bool> visited(V + 1, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);

            for (auto v : adj[node]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return result;
    }
};

// Driver code for testing
int main() {
    Graph g(5);

    g.addEdge(1, 2);
    g.addEdge(1, 5);
    g.addEdge(2, 3);
    g.addEdge(2, 4);

    vector<int> brute = g.bfsBrute(1);
    vector<int> optimal = g.bfsOptimal(1);

    cout << "BFS (Brute, Matrix): ";
    for (int x : brute) cout << x << " ";
    cout << endl;

    cout << "BFS (Optimal, List): ";
    for (int x : optimal) cout << x << " ";
    cout << endl;

    return 0;
}
