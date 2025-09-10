#include <bits/stdc++.h>
using namespace std;

// Function to build graph
void buildGraph(vector<string>& dict, int N, int K, vector<vector<int>>& adj, vector<int>& indegree) {
    for (int i = 0; i < N - 1; i++) {
        string w1 = dict[i], w2 = dict[i + 1];
        int len = min(w1.size(), w2.size());
        for (int j = 0; j < len; j++) {
            if (w1[j] != w2[j]) {
                adj[w1[j] - 'a'].push_back(w2[j] - 'a');
                indegree[w2[j] - 'a']++;
                break;
            }
        }
    }
}

// ---------------- Brute Force (DFS) ----------------
bool dfsUtil(int node, vector<vector<int>>& adj, vector<int>& visited, string& result) {
    visited[node] = 1; // visiting
    for (int nei : adj[node]) {
        if (visited[nei] == 1) return false; // cycle
        if (visited[nei] == 0) {
            if (!dfsUtil(nei, adj, visited, result)) return false;
        }
    }
    visited[node] = 2; // visited
    result.push_back((char)(node + 'a'));
    return true;
}

string alienOrderDFS(vector<string>& dict, int N, int K) {
    vector<vector<int>> adj(K);
    vector<int> indegree(K, 0);
    buildGraph(dict, N, K, adj, indegree);

    vector<int> visited(K, 0);
    string result;
    for (int i = 0; i < K; i++) {
        if (visited[i] == 0) {
            if (!dfsUtil(i, adj, visited, result)) return "";
        }
    }
    reverse(result.begin(), result.end());
    return result;
}

// ---------------- Optimal (Kahn’s BFS) ----------------
string alienOrderBFS(vector<string>& dict, int N, int K) {
    vector<vector<int>> adj(K);
    vector<int> indegree(K, 0);
    buildGraph(dict, N, K, adj, indegree);

    queue<int> q;
    for (int i = 0; i < K; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    string order;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        order.push_back((char)(node + 'a'));
        for (int nei : adj[node]) {
            indegree[nei]--;
            if (indegree[nei] == 0) q.push(nei);
        }
    }
    return order.size() == K ? order : "";
}

// ---------------- Main ----------------
int main() {
    int N = 5, K = 4;
    vector<string> dict = {"baa","abcd","abca","cab","cad"};

    cout << "Brute Force (DFS) Order: " << alienOrderDFS(dict, N, K) << endl;
    cout << "Optimal (BFS Kahn) Order: " << alienOrderBFS(dict, N, K) << endl;

    return 0;
}
