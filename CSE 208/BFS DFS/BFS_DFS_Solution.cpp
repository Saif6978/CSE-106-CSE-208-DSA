#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        if(u < 0 || v < 0 || u >= V || v >= V)
            return;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void removeEdge(int u, int v) {
        if(u < 0 || v < 0 || u >= V || v >= V)
            return;

        for(auto it = adj[u].begin(); it != adj[u].end(); it++) {
            if(*it == v) {
                adj[u].erase(it);
                break;
            }
        }

        for(auto it = adj[v].begin(); it != adj[v].end(); it++) {
            if(*it == u) {
                adj[v].erase(it);
                break;
            }
        }
    }

    void printGraph() {
        for(int i = 0; i < V; i++) {
            cout << i << " -> ";
            for(int x : adj[i])
                cout << x << " ";
            cout << endl;
        }
    }

    void checkBipartite() {
        vector<int> color(V, -1);

        for(int start = 0; start < V; start++) {
            if(color[start] != -1)
                continue;

            queue<int> q;
            q.push(start);
            color[start] = 0;

            while(!q.empty()) {
                int u = q.front();
                q.pop();

                for(int v : adj[u]) {
                    if(color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if(color[v] == color[u]) {
                        cout << "Not Bipartite" << endl;
                        return;
                    }
                }
            }
        }

        cout << "Bipartite" << endl;
    }
};

int main() {
    int v, e;
    cin >> v >> e;

    Graph g(v);

    for(int i = 0; i < e; i++) {
        int u, w;
        cin >> u >> w;
        g.addEdge(u, w);
    }

    g.checkBipartite();

    return 0;
}
