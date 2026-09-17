#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int time;
    int cost;
};
struct State {
    long long totalCost;
    int node;
    int timeSpent;
    int edgesUsed;
    bool operator>(const State& other) const {
        return totalCost > other.totalCost;
    }
};

int main() {
    int K;
    int N;
    int X;
    cin >> K;
    cin >> N;
    cin >> X;
    vector<vector<Edge>> graph(N + 1);
    for(int i = 0; i < X; i++) {
        int u, v, t, c;
        cin >> u >> v >> t >> c;
        // Undirected graph
        graph[u].push_back({v,t,c});
        graph[v].push_back({u,t,c});
    }
    int source, destination;
    cin >> source;
    cin >> destination;
    const long long INF = 1e18;
    vector<long long> dist(N+1, INF);
    vector<int> parent(N+1,-1);
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[source] = 0;
    pq.push({0, source, 0, 0});
    while(!pq.empty()) {
        State current = pq.top();
        pq.pop();
        int u = current.node;
        if(current.totalCost != dist[u]) continue;
        if(u == destination)break;
        for(auto edge : graph[u]) {
            long long newTime = current.timeSpent + edge.time;
            // waiting time added if this is not first bus
            if(current.edgesUsed > 0) newTime++;
            long long newCost = current.totalCost + edge.cost + (long long)K * (newTime - current.timeSpent);
            if(newCost < dist[edge.to]) {
                dist[edge.to] = newCost;
                parent[edge.to] = u;
                pq.push({ newCost, edge.to, (int)newTime, current.edgesUsed + 1 });
            }
        }
    }
    if(dist[destination] == INF) {
        cout << "Error\n";
        return 0;
    }
    // Reconstruct path
    vector<int> path;
    int current = destination;
    while(current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    // Print path
    for(int i = 0; i < path.size(); i++) {
        if(i) cout << "->";
        cout << path[i];
    }
    cout << " ";
    // Calculate total time
    int totalTime = 0;
    for(int i = 1; i < path.size(); i++) {
        int u = path[i-1];
        int v = path[i];
        for(auto e : graph[u]) {
            if(e.to == v) {
                totalTime += e.time;
                break;
            }
        }
        if(i > 1) totalTime++;
    }
    cout << totalTime << " ";
    cout << dist[destination] << endl;
    return 0;
}