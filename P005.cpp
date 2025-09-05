#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force Approach ----------
bool isValidColoring(vector<vector<int>>& adj, vector<int>& color) {
    int V = adj.size();
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            if (color[u] == color[v]) return false;
        }
    }
    return true;
}

bool bruteForceBipartite(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<int> color(V, 0);

    // Try all possible colorings (2^V)
    for (int mask = 0; mask < (1 << V); mask++) {
        for (int i = 0; i < V; i++) {
            color[i] = (mask & (1 << i)) ? 1 : 0;
        }
        if (isValidColoring(adj, color)) return true;
    }
    return false;
}

// ---------- Optimal DFS Approach ----------
bool dfs(int node, int c, vector<int>& color, vector<vector<int>>& adj) {
    color[node] = c;
    for (int neigh : adj[node]) {
        if (color[neigh] == -1) {
            if (!dfs(neigh, 1 - c, color, adj)) return false;
        } else if (color[neigh] == c) {
            return false;
        }
    }
    return true;
}

bool optimalBipartite(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<int> color(V, -1);

    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            if (!dfs(i, 0, color, adj)) return false;
        }
    }
    return true;
}

// ---------- Main Function ----------
int main() {
    int V = 4;
    vector<vector<int>> adj = {
        {1,3}, // 0 connected to 1,3
        {0,2}, // 1 connected to 0,2
        {1,3}, // 2 connected to 1,3
        {0,2}  // 3 connected to 0,2
    };

    cout << "Brute Force: " << (bruteForceBipartite(adj) ? "Yes" : "No") << endl;
    cout << "Optimal DFS: " << (optimalBipartite(adj) ? "Yes" : "No") << endl;

    return 0;
}
