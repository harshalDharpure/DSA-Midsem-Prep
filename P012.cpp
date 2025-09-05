#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force (Adjacency Matrix + DFS) ----------
void dfsMatrix(int node, vector<vector<int>>& adjMatrix, vector<int>& visited, vector<int>& result) {
    visited[node] = 1;
    result.push_back(node);
    for (int j = 0; j < adjMatrix.size(); j++) {
        if (adjMatrix[node][j] == 1 && !visited[j]) {
            dfsMatrix(j, adjMatrix, visited, result);
        }
    }
}

vector<int> bruteForceDFS(int V, vector<vector<int>>& edges) {
    vector<vector<int>> adjMatrix(V+1, vector<int>(V+1, 0));
    for (auto& e : edges) {
        adjMatrix[e[0]][e[1]] = 1;
        adjMatrix[e[1]][e[0]] = 1; // undirected
    }

    vector<int> visited(V+1, 0), result;
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) dfsMatrix(i, adjMatrix, visited, result);
    }
    return result;
}

// ---------- Optimal (Adjacency List + DFS) ----------
void dfsList(int node, vector<int> adj[], vector<int>& visited, vector<int>& result) {
    visited[node] = 1;
    result.push_back(node);
    for (auto nbr : adj[node]) {
        if (!visited[nbr]) dfsList(nbr, adj, visited, result);
    }
}

vector<int> optimalDFS(int V, vector<vector<int>>& edges) {
    vector<int> adj[V+1];
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    vector<int> visited(V+1, 0), result;
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) dfsList(i, adj, visited, result);
    }
    return result;
}

// ---------- Driver ----------
int main() {
    int V = 5;
    vector<vector<int>> edges = {{1,2},{1,3},{2,4},{2,5}};
    
    vector<int> brute = bruteForceDFS(V, edges);
    cout << "Brute Force DFS: ";
    for (int x : brute) cout << x << " ";
    cout << endl;

    vector<int> opt = optimalDFS(V, edges);
    cout << "Optimal DFS: ";
    for (int x : opt) cout << x << " ";
    cout << endl;

    return 0;
}
