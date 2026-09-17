#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    long long F;
    cin >> N >> M >> F;
    vector<int> capacity(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> capacity[i];
    }
    vector<vector<pair<int,int>>> graph(N + 1);
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Bidirectional road
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }
    int K;
    cin >> K;
    // ---------------------------
    // Dijkstra from Lab 1
    // ---------------------------
    const long long INF = 1e18;
    vector<long long> dist(N + 1, INF);
    priority_queue< pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    dist[1] = 0;
    pq.push({0,1});
    while(!pq.empty()) {
        auto [d,u] = pq.top();
        pq.pop();
        if(d != dist[u]) continue;
        for(auto [v,w] : graph[u]) {
            if(dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v],v});
            }
        }
    }
    // ---------------------------
    // Create lab priority queue
    // ---------------------------
    // {total cost, lab number}
    priority_queue< pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>> > labs;
    for(int i = 1; i <= N; i++) {
        long long totalCost = dist[i] + F;
        labs.push({totalCost,i});
    }
    // ---------------------------
    // Assign students
    // ---------------------------
    vector<long long> answer;
    for(int student = 0; student < K; student++) {
        while(!labs.empty() && capacity[labs.top().second] == 0) {
            labs.pop();
        }
        if(labs.empty()) {
            answer.push_back(-1);
        }
        else {
            auto [cost, lab] = labs.top();
            labs.pop();
            answer.push_back(cost);
            capacity[lab]--;
            // Still has space
            if(capacity[lab] > 0) {
                labs.push({cost,lab});
            }
        }
    }
    for(int i = 0; i < answer.size(); i++) {
        if(i) cout << " ";
        cout << answer[i];
    }
    cout << endl;
    return 0;
}