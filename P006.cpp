#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force Dijkstra (O(V^2)) ----------
vector<int> dijkstraBrute(int V, vector<vector<pair<int,int>>> &adj, int S) {
    vector<int> dist(V, INT_MAX);
    vector<bool> vis(V, false);
    dist[S] = 0;

    for (int count = 0; count < V - 1; count++) {
        // Pick minimum distance unvisited node
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!vis[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        vis[u] = true;
        for (auto &edge : adj[u]) {
            int v = edge.first, wt = edge.second;
            if (!vis[v] && dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }
    return dist;
}

// ---------- Optimal Dijkstra (Priority Queue) ----------
vector<int> dijkstraOptimal(int V, vector<vector<pair<int,int>>> &adj, int S) {
    vector<int> dist(V, INT_MAX);
    dist[S] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, S});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first, wt = edge.second;
            if (dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ---------- Main Function ----------
int main() {
    int V = 2;
    vector<vector<pair<int,int>>> adj(V);

    // Edge 0-1 with weight 9
    adj[0].push_back({1, 9});
    adj[1].push_back({0, 9});

    int S = 0;

    vector<int> distBrute = dijkstraBrute(V, adj, S);
    vector<int> distOptimal = dijkstraOptimal(V, adj, S);

    cout << "Brute Force Distances: ";
    for (int d : distBrute) cout << d << " ";
    cout << endl;

    cout << "Optimal Distances: ";
    for (int d : distOptimal) cout << d << " ";
    cout << endl;

    return 0;
}
