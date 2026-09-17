#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

bool dfs(vector<vector<char>>& graph, vector<vector<int>>& visited, int r, int c) {
    int n = graph.size();
    int m = graph[0].size();
    if (r < 0 || r >= n || c < 0 || c >= m) return false;
    if (visited[r][c] == 1 || graph[r][c] == '#') return false;
    if (graph[r][c] == 'S') return true;
    visited[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        if (dfs(graph, visited, r + dx[i], c + dy[i])) return true;
    }
    return false;
}

int main() {
    int n, m;
    if (!(cin >> n >> m) || n <= 0 || m <= 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<pair<int, int>> exits;
    vector<vector<char>> graph1(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> graph1[i][j];
            if (graph1[i][j] == 'E') {
                exits.push_back({i, j});
            }
        }
    }
    int counter = 0;
    for (size_t i = 0; i < exits.size(); i++) {
        vector<vector<int>> visited(n, vector<int>(m, 0));
        if (dfs(graph1, visited, exits[i].first, exits[i].second)) {
            counter++;
        }
    }
    cout << counter << endl;
    return 0;
}
