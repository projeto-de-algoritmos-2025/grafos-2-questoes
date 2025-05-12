#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        pq.push({grid[0][0], {0, 0}});
        visited[0][0] = true;
        int maxTime = 0;

        int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        while (!pq.empty()) {
            auto current = pq.top();
            pq.pop();
            int time = current.first;
            int x = current.second.first;
            int y = current.second.second;

            maxTime = max(maxTime, time);

            if (x == n-1 && y == n-1) {
                return maxTime;
            }

            for (auto& dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];

                if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    pq.push({grid[nx][ny], {nx, ny}});
                }
            }
        }

        return -1;
    }
};