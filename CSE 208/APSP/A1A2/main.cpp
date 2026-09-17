#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
int main() {
    int N, M, K, X;
    cin >> N >> M >> K >> X;
    vector<int> start(K);
    for(int i = 0; i < K; i++) cin >> start[i];
    vector<int> rate(K);
    for(int i = 0; i < K; i++) cin >> rate[i];
    vector<vector<long long>> dist( N + 1, vector<long long>(N + 1, INF) );
    vector<vector<int>> nextNode(N + 1,vector<int>(N + 1, -1) );
    for(int i = 1; i <= N; i++) {
        dist[i][i] = 0;
        nextNode[i][i] = i;
    }
    for(int i = 0; i < M; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        if(t < dist[u][v]) {
            dist[u][v] = t;
            dist[v][u] = t;
            nextNode[u][v] = v;
            nextNode[v][u] = u;
        }
    }
    // Floyd-Warshall APSP
    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextNode[i][j] = nextNode[i][k];
                }
            }
        }
    }
    int meetingCity = -1;
    long long bestCost = INF;
    int lastTime = 0;
    // Find best meeting city
    for(int city = 1; city <= N; city++) {
        long long totalCost = 0;
        int maximumTime = 0;
        bool possible = true;
        for(int i = 0; i < K; i++) {
            int t = dist[start[i]][city];
            if(t == INF || t > X) {
                possible = false;
                break;
            }
            totalCost += 1LL * rate[i] * t;
            maximumTime = max( maximumTime, t);
        }
        if(possible && totalCost < bestCost) {
            bestCost = totalCost;
            meetingCity = city;
            lastTime = maximumTime;
        }
    }
    if(meetingCity == -1) {
        cout << "No meeting\n";
        return 0;
    }
    cout  << meetingCity << " " << bestCost << " " << lastTime << "\n";
    // Print each lord path
    for(int i = 0; i < K; i++) {
        int u = start[i];
        int v = meetingCity;
        vector<int> path;
        if(u == v) {
            path.push_back(u);
        }
        else {
            while(u != v) {
                path.push_back(u);
                u = nextNode[u][v];
            }
            path.push_back(v);
        }
        for(int j = 0; j < path.size(); j++) {
            if(j) cout << " -> ";
            cout << path[j];
        }
        cout << " " << 1LL * rate[i] * dist[start[i]][meetingCity] << "\n";
    }
    return 0;
}