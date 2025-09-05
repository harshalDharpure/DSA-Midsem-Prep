#include <bits/stdc++.h>
using namespace std;

int n, m;

// Directions for Up, Down, Left, Right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// ---------- Brute Force DFS ----------
int dfsUtil(vector<vector<int>>& grid, vector<vector<bool>>& vis, int x, int y, int dxn, int dyn, int dist) {
    if (x == dxn && y == dyn) return dist;

    int ans = INT_MAX;
    vis[x][y] = true;

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !vis[nx][ny]) {
            ans = min(ans, dfsUtil(grid, vis, nx, ny, dxn, dyn, dist + 1));
        }
    }

    vis[x][y] = false; // backtrack
    return ans;
}

int shortestPathBrute(vector<vector<int>>& grid, pair<int,int> src, pair<int,int> dest) {
    n = grid.size();
    m = grid[0].size();
    if (grid[src.first][src.second] == 0 || grid[dest.first][dest.second] == 0)
        return -1;

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    int res = dfsUtil(grid, vis, src.first, src.second, dest.first, dest.second, 0);
    return (res == INT_MAX ? -1 : res);
}

// ---------- Optimal BFS ----------
int shortestPathOptimal(vector<vector<int>>& grid, pair<int,int> src, pair<int,int> dest) {
    n = grid.size();
    m = grid[0].size();
    if (grid[src.first][src.second] == 0 || grid[dest.first][dest.second] == 0)
        return -1;

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<pair<int,int>> q;

    dist[src.first][src.second] = 0;
    q.push(src);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == dest.first && y == dest.second) return dist[x][y];

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1) {
                if (dist[x][y] + 1 < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    return -1;
}

// ---------- Main Function ----------
int main() {
    vector<vector<int>> grid = {
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0},
        {1, 0, 0, 1}
    };

    pair<int,int> source = {0, 1};
    pair<int,int> destination = {2, 2};

    cout << "Brute Force: " << shortestPathBrute(grid, source, destination) << endl;
    cout << "Optimal BFS: " << shortestPathOptimal(grid, source, destination) << endl;

    return 0;
}
