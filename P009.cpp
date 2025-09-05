#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

// ---------- Brute Force DFS ----------
void dfs(int node, int n, vector<vector<pair<int,int>>>& adj, 
         int time, int& minTime, int& count) {
    if (node == n-1) {
        if (time < minTime) {
            minTime = time;
            count = 1;
        } else if (time == minTime) {
            count++;
        }
        return;
    }
    for (auto [next, wt] : adj[node]) {
        dfs(next, n, adj, time + wt, minTime, count);
    }
}

int bruteForceWays(int n, vector<vector<int>>& roads) {
    vector<vector<pair<int,int>>> adj(n);
    for (auto& e : roads) {
        adj[e[0]].push_back({e[1], e[2]});
        adj[e[1]].push_back({e[0], e[2]});
    }
    int minTime = INT_MAX, count = 0;
    dfs(0, n, adj, 0, minTime, count);
    return count % MOD;
}

// ---------- Optimal Dijkstra ----------
int countWays(int n, vector<vector<int>>& roads) {
    vector<vector<pair<int,int>>> adj(n);
    for (auto& e : roads) {
        adj[e[0]].push_back({e[1], e[2]});
        adj[e[1]].push_back({e[0], e[2]});
    }
    
    vector<long long> dist(n, LLONG_MAX);
    vector<int> ways(n, 0);
    priority_queue<pair<long long,int>, 
                   vector<pair<long long,int>>, 
                   greater<>> pq;
    
    dist[0] = 0;
    ways[0] = 1;
    pq.push({0,0});
    
    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v,w] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                ways[v] = ways[u];
                pq.push({dist[v], v});
            } else if (dist[v] == d + w) {
                ways[v] = (ways[v] + ways[u]) % MOD;
            }
        }
    }
    return ways[n-1];
}

// ---------- Driver ----------
int main() {
    int n = 7;
    vector<vector<int>> roads = {
        {0,6,7},{0,1,2},{1,2,3},{1,3,3},
        {6,3,3},{3,5,1},{6,5,1},{2,5,1},
        {0,4,5},{4,6,2}
    };
    
    cout << "Brute Force Ways: " << bruteForceWays(n, roads) << endl;
    cout << "Optimal Ways: " << countWays(n, roads) << endl;
    
    return 0;
}
