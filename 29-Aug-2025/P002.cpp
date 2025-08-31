#include <bits/stdc++.h>
using namespace std;

// Brute Force: Using DFS
void dfs(int node, vector<vector<int>> &adj, vector<int> &visited) {
    visited[node] = 1;
    for (int j = 0; j < adj.size(); j++) {
        if (adj[node][j] == 1 && !visited[j]) {
            dfs(j, adj, visited);
        }
    }
}

int numberOfProvincesBrute(vector<vector<int>> &adj) {
    int V = adj.size();
    vector<int> visited(V, 0);
    int count = 0;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited);
            count++;
        }
    }
    return count;
}

// Optimal Approach: Using DSU (Disjoint Set Union)
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]); // path compression
    }
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            if (rank[px] < rank[py]) parent[px] = py;
            else if (rank[py] < rank[px]) parent[py] = px;
            else {
                parent[py] = px;
                rank[px]++;
            }
        }
    }
};

int numberOfProvincesOptimal(vector<vector<int>> &adj) {
    int V = adj.size();
    DSU dsu(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adj[i][j] == 1) {
                dsu.unite(i, j);
            }
        }
    }
    int count = 0;
    for (int i = 0; i < V; i++) {
        if (dsu.find(i) == i) count++;
    }
    return count;
}

// Main function to test
int main() {
    vector<vector<int>> adj = {
        {1,1,0,0,0,0,0,0},
        {1,1,1,0,0,0,0,0},
        {0,1,1,0,0,0,0,0},
        {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,1,0,0},
        {0,0,0,0,1,1,0,0},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1}
    };

    cout << "Brute Force Provinces = " << numberOfProvincesBrute(adj) << endl;
    cout << "Optimal DSU Provinces = " << numberOfProvincesOptimal(adj) << endl;

    return 0;
}
