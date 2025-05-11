#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class UnionFind {
public:
    vector<int> parent, rank;
    UnionFind(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false;
        if (rank[xr] < rank[yr]) parent[xr] = yr;
        else if (rank[xr] > rank[yr]) parent[yr] = xr;
        else { parent[yr] = xr; rank[xr]++; }
        return true;
    }
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        vector<vector<int>> newEdges;
        for (int i = 0; i < m; ++i) {
            newEdges.push_back({edges[i][0], edges[i][1], edges[i][2], i});
        }
        // Ordena por peso
        sort(newEdges.begin(), newEdges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        auto kruskal = [&](int n, vector<vector<int>>& edges, int excludeEdge, int includeEdge) {
            UnionFind uf(n);
            int weight = 0, count = 0;
            if (includeEdge != -1) {
                uf.unite(edges[includeEdge][0], edges[includeEdge][1]);
                weight += edges[includeEdge][2];
                count++;
            }
            for (int i = 0; i < edges.size(); ++i) {
                if (i == excludeEdge) continue;
                if (uf.unite(edges[i][0], edges[i][1])) {
                    weight += edges[i][2];
                    count++;
                }
            }
            return count == n - 1 ? weight : INT_MAX;
        };

        int minWeight = kruskal(n, newEdges, -1, -1);
        vector<int> critical, pseudoCritical;

        for (int i = 0; i < m; ++i) {
            if (kruskal(n, newEdges, i, -1) > minWeight) {
                critical.push_back(newEdges[i][3]);
            } else if (kruskal(n, newEdges, -1, i) == minWeight) {
                pseudoCritical.push_back(newEdges[i][3]);
            }
        }
        return {critical, pseudoCritical};
    }
};
