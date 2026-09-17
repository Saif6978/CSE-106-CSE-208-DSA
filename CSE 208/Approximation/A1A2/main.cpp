#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> graph;
vector<vector<int>> adj;
vector<int> visited;
vector<int> tour;

void dfs(int u) {
    visited[u] = 1;
    tour.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v])
            dfs(v);
    }
}

void primMST() {
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> used(n, false);
    key[0] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (u == -1 || key[j] < key[u])) u = j;
        }
        if (u == -1) break;
        used[u] = true;
        for (int v = 0; v < n; v++) {
            if (u != v && !used[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    adj.assign(n, vector<int>());
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            adj[i].push_back(parent[i]);
            adj[parent[i]].push_back(i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    if (n <= 0) {
        cout << 0 << "\n\n";
        return 0;
    }
    graph.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> graph[i][j];
    }
    if (n == 1) {
        cout << 0 << "\n0 0\n";
        return 0;
    }

    primMST();
    visited.assign(n, 0);
    dfs(0);
    tour.push_back(0);

    int cost = 0;
    for (int i = 0; i < (int)tour.size() - 1; i++) {
        cost += graph[tour[i]][tour[i + 1]];
    }
    cout << cost << "\n";
    for (int i = 0; i < (int)tour.size(); i++) {
        cout << tour[i] << (i + 1 == (int)tour.size() ? "" : " ");
    }
    cout << "\n";
    return 0;
}