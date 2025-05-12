#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& edge : times) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
        }

        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, k});

        while (!pq.empty()) {
            pair<int, int> current = pq.top();
            int time = current.first;
            int u = current.second;
            pq.pop();

            if (time > dist[u]) continue;

            for (const auto& edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        int max_time = *max_element(dist.begin() + 1, dist.end());
        return (max_time == INT_MAX) ? -1 : max_time;
    }
};