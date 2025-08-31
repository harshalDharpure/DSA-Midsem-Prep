#include <bits/stdc++.h>
using namespace std;

// ------------------- BRUTE FORCE -------------------
vector<vector<int>> nearestDistanceBruteForce(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> ans(n, vector<int>(m, INT_MAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                ans[i][j] = 0;
            } else {
                int minDist = INT_MAX;
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < m; y++) {
                        if (grid[x][y] == 1) {
                            minDist = min(minDist, abs(i - x) + abs(j - y));
                        }
                    }
                }
                ans[i][j] = minDist;
            }
        }
    }
    return ans;
}

// ------------------- OPTIMAL (BFS) -------------------
vector<vector<int>> nearestDistanceOptimal(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    // Push all 1's into queue as BFS starting points
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                dist[i][j] = 0;
                q.push(make_pair(i, j)); // old style for compatibility
            }
        }
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        pair<int, int> front = q.front(); q.pop();
        int i = front.first;
        int j = front.second;

        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if (ni >= 0 && ni < n && nj >= 0 && nj < m && dist[ni][nj] == -1) {
                dist[ni][nj] = dist[i][j] + 1;
                q.push(make_pair(ni, nj));
            }
        }
    }

    return dist;
}

// ------------------- MAIN -------------------
int main() {
    vector<vector<int>> grid = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 0}
    };

    cout << "Brute Force Output:\n";
    auto ans1 = nearestDistanceBruteForce(grid);
    for (auto &row : ans1) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    cout << "\nOptimal (BFS) Output:\n";
    auto ans2 = nearestDistanceOptimal(grid);
    for (auto &row : ans2) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    return 0;
}
