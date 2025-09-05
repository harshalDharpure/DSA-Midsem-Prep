#include <bits/stdc++.h>
using namespace std;

// Directions (up, right, down, left)
int dRow[4] = {-1, 0, 1, 0};
int dCol[4] = {0, 1, 0, -1};

// ---------------- Brute Force: DFS ----------------
void dfs(int row, int col, vector<vector<int>>& image, int oldColor, int newColor) {
    int n = image.size();
    int m = image[0].size();

    // Boundary + already processed check
    if (row < 0 || col < 0 || row >= n || col >= m || image[row][col] != oldColor) return;

    // Change colour
    image[row][col] = newColor;

    // DFS in 4 directions
    for (int i = 0; i < 4; i++) {
        dfs(row + dRow[i], col + dCol[i], image, oldColor, newColor);
    }
}

vector<vector<int>> floodFillDFS(vector<vector<int>> image, int sr, int sc, int newColor) {
    int oldColor = image[sr][sc];
    if (oldColor != newColor) {
        dfs(sr, sc, image, oldColor, newColor);
    }
    return image;
}

// ---------------- Optimal: BFS ----------------
vector<vector<int>> floodFillBFS(vector<vector<int>> image, int sr, int sc, int newColor) {
    int n = image.size();
    int m = image[0].size();
    int oldColor = image[sr][sc];

    if (oldColor == newColor) return image;

    queue<pair<int, int>> q;
    q.push({sr, sc});
    image[sr][sc] = newColor;

    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nRow = row + dRow[i];
            int nCol = col + dCol[i];

            if (nRow >= 0 && nCol >= 0 && nRow < n && nCol < m && image[nRow][nCol] == oldColor) {
                image[nRow][nCol] = newColor;
                q.push({nRow, nCol});
            }
        }
    }
    return image;
}

// ---------------- Main ----------------
int main() {
    vector<vector<int>> image = {
        {1,1,1},
        {2,2,0},
        {2,2,2}
    };

    int sr = 2, sc = 0, newColor = 3;

    // Brute Force (DFS)
    vector<vector<int>> resultDFS = floodFillDFS(image, sr, sc, newColor);

    cout << "DFS Result:\n";
    for (auto &row : resultDFS) {
        for (auto &cell : row) cout << cell << " ";
        cout << "\n";
    }

    // Reset image for BFS
    image = {
        {1,1,1},
        {2,2,0},
        {2,2,2}
    };

    // Optimal (BFS)
    vector<vector<int>> resultBFS = floodFillBFS(image, sr, sc, newColor);

    cout << "\nBFS Result:\n";
    for (auto &row : resultBFS) {
        for (auto &cell : row) cout << cell << " ";
        cout << "\n";
    }

    return 0;
}
