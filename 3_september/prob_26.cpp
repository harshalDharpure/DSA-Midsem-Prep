#include <bits/stdc++.h>
using namespace std;

/* =========================================================
   Brute Force Approach: DFS + Cycle Detection
   ========================================================= */
class BruteForce {
public:
    bool dfs(int node, vector<vector<int>> &adj, vector<int> &vis, vector<int> &pathVis, vector<int> &safe) {
        vis[node] = 1;
        pathVis[node] = 1;

        for (auto it : adj[node]) {
            if (!vis[it]) {
                if (dfs(it, adj, vis, pathVis, safe) == true)
                    return true;
            }
            else if (pathVis[it]) {
                return true; // cycle detected
            }
        }

        pathVis[node] = 0;
        safe[node] = 1;  // safe node
        return false;
    }

    vector<int> eventualSafeNodes(int V, vector<vector<int>> &adj) {
        vector<int> vis(V, 0), pathVis(V, 0), safe(V, 0);

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, adj, vis, pathVis, safe);
            }
        }

        vector<int> result;
        for (int i = 0; i < V; i++) {
            if (safe[i]) result.push_back(i);
        }
        return result;
    }
};

/* =========================================================
   Optimal Approach: BFS + Topological Sort (Kahn's Algo)
   ========================================================= */
class Optimal {
public:
    vector<int> eventualSafeNodes(int V, vector<vector<int>> &adj) {
        vector<vector<int>> revAdj(V);
        vector<int> indegree(V, 0);

        // Build reverse graph
        for (int u = 0; u < V; u++) {
            for (auto v : adj[u]) {
                revAdj[v].push_back(u);
                indegree[u]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> safe;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safe.push_back(node);

            for (auto it : revAdj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        sort(safe.begin(), safe.end());
        return safe;
    }
};

/* =========================================================
   Driver Code
   ========================================================= */
int main() {
    int V = 7, E = 7;
    vector<vector<int>> adj(V);

    // Example edges
    adj[0] = {1, 2};
    adj[1] = {2, 3};
    adj[2] = {5};
    adj[3] = {0};
    adj[4] = {5};
    adj[5] = {};
    adj[6] = {};

    // Brute Force
    BruteForce brute;
    vector<int> bruteRes = brute.eventualSafeNodes(V, adj);
    cout << "Brute Force Safe Nodes: ";
    for (int x : bruteRes) cout << x << " ";
    cout << endl;

    // Optimal
    Optimal opt;
    vector<int> optRes = opt.eventualSafeNodes(V, adj);
    cout << "Optimal Safe Nodes: ";
    for (int x : optRes) cout << x << " ";
    cout << endl;

    return 0;
}
