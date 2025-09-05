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

    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        if (rank[px] < rank[py]) parent[px] = py;
        else if (rank[px] > rank[py]) parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

// ---------- Brute Force (DFS for components) ----------
void dfs(int idx, vector<vector<int>>& stones, vector<int>& vis) {
    vis[idx] = 1;
    for (int j = 0; j < stones.size(); j++) {
        if (!vis[j] && (stones[idx][0] == stones[j][0] || stones[idx][1] == stones[j][1])) {
            dfs(j, stones, vis);
        }
    }
}

int bruteForceOps(vector<vector<int>>& stones) {
    int n = stones.size();
    vector<int> vis(n, 0);
    int components = 0;

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            components++;
            dfs(i, stones, vis);
        }
    }
    return n - components;
}

// ---------- Optimal DSU ----------
int dsuOps(vector<vector<int>>& stones) {
    int n = stones.size();
    int maxRow = 0, maxCol = 0;
    for (auto& s : stones) {
        maxRow = max(maxRow, s[0]);
        maxCol = max(maxCol, s[1]);
    }

    DSU dsu(maxRow + maxCol + 2); // row + col space
    unordered_set<int> nodesUsed;

    for (auto& s : stones) {
        int rowNode = s[0];
        int colNode = s[1] + maxRow + 1; // offset
        dsu.unite(rowNode, colNode);
        nodesUsed.insert(rowNode);
        nodesUsed.insert(colNode);
    }

    int components = 0;
    for (auto node : nodesUsed) {
        if (dsu.find(node) == node) components++;
    }

    return n - components;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> stones1 = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    cout << "Brute Force (Ex1): " << bruteForceOps(stones1) << endl;
    cout << "DSU Optimal (Ex1): " << dsuOps(stones1) << endl;

    vector<vector<int>> stones2 = {{0,0},{0,2},{1,3},{3,1},{3,2},{4,3}};
    cout << "Brute Force (Ex2): " << bruteForceOps(stones2) << endl;
    cout << "DSU Optimal (Ex2): " << dsuOps(stones2) << endl;

    return 0;
}
