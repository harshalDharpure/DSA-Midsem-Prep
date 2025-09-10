#include <bits/stdc++.h>
using namespace std;

// ----------------- Brute Force -----------------
vector<int> shortestPathBrute(int N, vector<pair<int,int>>& edges, int src) {
    vector<int> dist(N, INT_MAX);
    dist[src] = 0;

    // Relax edges N-1 times
    for (int i = 0; i < N - 1; i++) {
        for (auto &e : edges) {
            int u = e.first, v = e.second;
            if (dist[u] != INT_MAX && dist[u] + 1 < dist[v])
                dist[v] = dist[u] + 1;
            if (dist[v] != INT_MAX && dist[v] + 1 < dist[u])
                dist[u] = dist[v] + 1;
        }
    }

    for (int i = 0; i < N; i++) if (dist[i] == INT_MAX) dist[i] = -1;
    return dist;
}

// ----------------- Optimal BFS -----------------
vector<int> shortestPathBFS(int N, vector<pair<int,int>>& edges, int src) {
    vector<vector<int>> adj(N);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first); // undirected
    }

    vector<int> dist(N, INT_MAX);
    queue<int> q;
    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < N; i++) if (dist[i] == INT_MAX) dist[i] = -1;
    return dist;
}

// ----------------- Main -----------------
int main() {
    int N = 9, M = 10, src = 0;
    vector<pair<int,int>> edges = {
        {0,1},{0,3},{3,4},{4,5},{5,6},
        {1,2},{2,6},{6,7},{7,8},{6,8}
    };

    vector<int> ans1 = shortestPathBrute(N, edges, src);
    vector<int> ans2 = shortestPathBFS(N, edges, src);

    cout << "Brute Force: ";
    for (int x : ans1) cout << x << " ";
    cout << endl;

    cout << "Optimal BFS: ";
    for (int x : ans2) cout << x << " ";
    cout << endl;

    return 0;
}
