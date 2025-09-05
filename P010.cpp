#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank[px] < rank[py]) parent[px] = py;
        else if (rank[px] > rank[py]) parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

// ---------- Brute Force (DFS + edge counting) ----------
void dfs(int node, vector<int> adj[], vector<int>& vis) {
    vis[node] = 1;
    for (auto nxt : adj[node]) {
        if (!vis[nxt]) dfs(nxt, adj, vis);
    }
}

int bruteForceOps(int n, vector<vector<int>>& edges) {
    if ((int)edges.size() < n-1) return -1;

    // Count components
    vector<int> adj[n];
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    vector<int> vis(n, 0);
    int components = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            components++;
            dfs(i, adj, vis);
        }
    }
    int extraEdges = edges.size() - ((n - components) + (components - 1));
    return (components - 1 <= extraEdges) ? (components - 1) : -1;
}

// ---------- Optimal DSU ----------
int dsuOps(int n, vector<vector<int>>& edges) {
    if ((int)edges.size() < n-1) return -1;

    DSU dsu(n);
    int extraEdges = 0;
    for (auto& e : edges) {
        if (!dsu.unite(e[0], e[1])) extraEdges++;
    }

    int components = 0;
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i) components++;
    }

    return (extraEdges >= components - 1) ? (components - 1) : -1;
}

// ---------- Driver ----------
int main() {
    int n1 = 4;
    vector<vector<int>> edges1 = {{0,1},{0,2},{1,2}};
    cout << "Brute Force Ops (Ex1): " << bruteForceOps(n1, edges1) << endl;
    cout << "DSU Ops (Ex1): " << dsuOps(n1, edges1) << endl;

    int n2 = 9;
    vector<vector<int>> edges2 = {
        {0,1},{0,2},{0,3},{1,2},{2,3},
        {4,5},{5,6},{7,8}
    };
    cout << "Brute Force Ops (Ex2): " << bruteForceOps(n2, edges2) << endl;
    cout << "DSU Ops (Ex2): " << dsuOps(n2, edges2) << endl;

    return 0;
}
