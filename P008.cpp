#include <bits/stdc++.h>
using namespace std;

int n, m;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// ---------- Brute Force DFS ----------
int dfsUtil(vector<vector<int>>& heights, vector<vector<bool>>& vis, int x, int y, int destx, int desty, int currEffort) {
    if (x == destx && y == desty) return currEffort;

    vis[x][y] = true;
    int ans = INT_MAX;

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
            int newEffort = max(currEffort, abs(heights[nx][ny] - heights[x][y]));
            ans = min(ans, dfsUtil(heights, vis, nx, ny, destx, desty, newEffort));
        }
    }

    vis[x][y] = false; // backtrack
    return ans;
}

int bruteForcePathMinEffort(vector<vector<int>>& heights) {
    n = heights.size();
    m = heights[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    int res = dfsUtil(heights, vis, 0, 0, n - 1, m - 1, 0);
    return (res == INT_MAX ? -1 : res);
}

// ---------- Optimal Dijkstra ----------
int optimalPathMinEffort(vector<vector<int>>& heights) {
    n = heights.size();
    m = heights[0].size();

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    dist[0][0] = 0;

    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    pq.push({0, 0, 0}); // {effort, row, col}

    while (!pq.empty()) {
        auto [effort, x, y] = pq.top();
        pq.pop();

        if (x == n - 1 && y == m - 1) return effort;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                int newEffort = max(effort, abs(heights[nx][ny] - heights[x][y]));
                if (newEffort < dist[nx][ny]) {
                    dist[nx][ny] = newEffort;
                    pq.push({newEffort, nx, ny});
                }
            }
        }
    }

    return -1; // unreachable (shouldn't happen in valid inputs)
}

// ---------- Main Function ----------
int main() {
    vector<vector<int>> heights1 = {{1,2,2}, {3,8,2}, {5,3,5}};
    vector<vector<int>> heights2 = {
        {1,2,1,1,1},
        {1,2,1,2,1},
        {1,2,1,2,1},
        {1,1,1,2,1}
    };

    cout << "Example 1:" << endl;
    cout << "Brute Force: " << bruteForcePathMinEffort(heights1) << endl;
    cout << "Optimal: " << optimalPathMinEffort(heights1) << endl;

    cout << "\nExample 2:" << endl;
    cout << "Brute Force: " << bruteForcePathMinEffort(heights2) << endl;
    cout << "Optimal: " << optimalPathMinEffort(heights2) << endl;

    return 0;
}
