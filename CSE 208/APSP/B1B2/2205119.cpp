#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> start(N + 1);
    vector<int> target(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> start[i];
    }
    for(int i = 1; i <= N; i++) {
        cin >> target[i];
    }
    const long long INF = 1e18;
    vector<vector<long long>> dist( N + 1, vector<long long>(N + 1, INF) );
    // Distance from a node to itself is zero
    for(int i = 1; i <= N; i++) {
        dist[i][i] = 0;
    }
    // Read directed roads
    for(int i = 0; i < M; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // Keep minimum edge if multiple roads exist
        dist[u][v] = min(dist[u][v], w);
    }
    /*
        Floyd-Warshall APSP
        Finds minimum cost between
        every pair of stations.
    */
    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= N; i++) {
            if(dist[i][k] == INF) continue;
            for(int j = 1; j <= N; j++) {
                if(dist[k][j] == INF) continue;
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    /*
        Calculate every reachable army cost
    */
    vector<long long> costs;
    for(int i = 1; i <= N; i++) {
        long long pathCost = dist[start[i]][target[i]];
        // Ignore unreachable armies
        if(pathCost != INF) {
            costs.push_back(pathCost);
        }
    }
    /*
        To minimize doubling effect:
        expensive armies should go first.
        Example:
        Batch 1 -> x1
        Batch 2 -> x2
        Batch 3 -> x4
    */
    sort(costs.begin(), costs.end(), greater<long long>());
    long long answer = 0;
    long long multiplier = 1;
    for(int i = 0; i < costs.size(); i++) {
        if(i != 0 && i % K == 0) {
            multiplier *= 2;
        }
        answer += costs[i] * multiplier;
    }
    cout << answer << endl;
    return 0;
}