#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

int main() {
    int n, m, k, b, e;
    cin >> n >> m >> k >> b >> e;
    vector<int> capitals(k);
    for(int i = 0; i < k; i++) cin >> capitals[i];
    vector<bool> blocked(n + 1, false);
    for(int i = 0; i < b; i++) {
        int x;
        cin >> x;
        blocked[x] = true;
    }
    vector<int> emergency(e);
    for(int i = 0; i < e; i++) cin >> emergency[i];
    vector<Edge> edges;
    for(int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // blocked cities are removed
        if(blocked[u] || blocked[v])
            continue;
        edges.push_back({u, v, w});
    }
    const long long INF = LLONG_MAX / 4;
    /*
        Multi-source Bellman-Ford
        All capitals are starting points,
        therefore distance = 0
    */
    vector<long long> dist(n + 1, INF);
    for(int c : capitals) {
        if(!blocked[c])
            dist[c] = 0;
    }
    /*
        Relax all edges n-1 times
    */
    for(int i = 1; i <= n - 1; i++) {
        bool changed = false;
        for(auto edge : edges) {
            int u = edge.u;
            int v = edge.v;
            long long w = edge.w;
            if(dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if(!changed) break;
    }
    /*
        Negative cycle detection
        If we can still relax an edge,
        a reachable negative cycle exists.
    */
    for(auto edge : edges) {
        int u = edge.u;
        int v = edge.v;
        long long w = edge.w;
        if(dist[u] != INF && dist[v] > dist[u] + w) {
            cout << "Abyss Detected\n";
            return 0;
        }
    }
    /*
        Print answers for emergency posts
    */
    for(int i = 0; i < e; i++) {
        int node = emergency[i];
        if(dist[node] == INF) cout << "INF\n";
        else cout << dist[node] << "\n";
    }
    return 0;
}