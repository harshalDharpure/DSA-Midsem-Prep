#include <bits/stdc++.h>
using namespace std;

// Optimal BFS
int orangesRottingOptimal(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<pair<int,int>, int>> q; // {{i,j}, time}
    int fresh = 0;
    
    // Step 1: Push all rotten oranges
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                q.push(make_pair(make_pair(i,j), 0));
            }
            if (grid[i][j] == 1) fresh++;
        }
    }
    
    int maxTime = 0;
    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    // Step 2: BFS
    while (!q.empty()) {
        pair<pair<int,int>, int> front = q.front();
        q.pop();
        
        int i = front.first.first;
        int j = front.first.second;
        int t = front.second;
        
        maxTime = max(maxTime, t);
        
        for (int d = 0; d < 4; d++) {
            int ni = i + dirs[d][0];
            int nj = j + dirs[d][1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 1) {
                grid[ni][nj] = 2;
                fresh--;
                q.push(make_pair(make_pair(ni,nj), t+1));
            }
        }
    }
    
    return (fresh == 0) ? maxTime : -1;
}

int main() {
    vector<vector<int>> grid = {
        {2,1,1},
        {0,1,1},
        {1,0,1}
    };

    cout << "Optimal BFS Result = " << orangesRottingOptimal(grid) << endl;
    return 0;
}
