#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> capGraph, flowNetwork;
vector<vector<int>> adj;

bool bfs(int s, int t, vector<int>& parent) {
    vector<bool> vis(N + 1, false);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!vis[v] && capGraph[u][v] > 0) {
                parent[v] = u;
                vis[v] = true;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int maxFlow(int s, int t) {
    int totalFlow = 0;
    vector<int> parent(N + 1);

    while (bfs(s, t, parent)) {
        int path = INT_MAX;
        for (int v = t; v != s; v = parent[v])
            path = min(path, capGraph[parent[v]][v]);

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capGraph[u][v] -= path;
            capGraph[v][u] += path;
            flowNetwork[u][v] += path;
            flowNetwork[v][u] -= path;
        }
        totalFlow += path;
    }
    return totalFlow;
}

bool getPath(int u, int t, vector<int>& path, vector<bool>& vis) {
    path.push_back(u);
    if (u == t) return true;
    vis[u] = true;

    for (int v : adj[u]) {
        if (!vis[v] && flowNetwork[u][v] > 0) {
            if (getPath(v, t, path, vis)) {
                flowNetwork[u][v]--;
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    for (int tc = 1; tc <= T; tc++) {
        int M;
        cin >> N >> M;

        capGraph.assign(N + 1, vector<int>(N + 1, 0));
        flowNetwork.assign(N + 1, vector<int>(N + 1, 0));
        adj.assign(N + 1, {});

        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            capGraph[u][v] = 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int flow = maxFlow(1, N);

        cout << "Case " << tc << ": " << flow << "\n";

        if (flow == 0) {
            cout << "No escape route possible! The Professor needs a new plan.\n";
        } else {
            for (int i = 0; i < flow; i++) {
                vector<int> path;
                vector<bool> vis(N + 1, false);
                getPath(1, N, path, vis);

                for (size_t j = 0; j < path.size(); j++) {
                    if (j) cout << " -> ";
                    cout << path[j];
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
