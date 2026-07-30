#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

long long manhattan(const Point& a, const Point& b) {
    return llabs((long long)a.x - b.x) + llabs((long long)a.y - b.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;  // No input

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // Prim's algorithm for dense graph (complete graph)
    const long long INF = 4e18;
    vector<long long> minDist(n, INF);
    vector<bool> inMST(n, false);

    minDist[0] = 0;
    long long totalCost = 0;

    for (int i = 0; i < n; ++i) {
        // Select the unvisited vertex with the smallest distance
        int u = -1;
        long long best = INF;
        for (int j = 0; j < n; ++j) {
            if (!inMST[j] && minDist[j] < best) {
                best = minDist[j];
                u = j;
            }
        }

        if (u == -1) break;  // Should never happen because graph is connected

        inMST[u] = true;
        totalCost += best;

        // Update distances to all other unvisited vertices
        for (int v = 0; v < n; ++v) {
            if (!inMST[v]) {
                long long w = manhattan(points[u], points[v]);
                if (w < minDist[v]) {
                    minDist[v] = w;
                }
            }
        }
    }

    cout << totalCost << '\n';
    return 0;
}