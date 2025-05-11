#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> inMST(n, false);
        vector<int> minDist(n, INT_MAX);
        minDist[0] = 0;
        int result = 0;
        int edgesUsed = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>,    greater<pair<int, int>>> pq;
        pq.push({0, 0});

        while (edgesUsed < n) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;
            result += cost;
            edgesUsed++;

            for (int v = 0; v < n; ++v) {
                if (!inMST[v]) {
                    int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    if (dist < minDist[v]) {
                        minDist[v] = dist;
                        pq.push({dist, v});
                    }
                }
            }
        }
        return result;
    }
};
