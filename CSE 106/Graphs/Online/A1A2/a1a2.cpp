#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // reverse adjacency list: rev[b] contains all prerequisites a of b
    vector<vector<int>> rev(N + 1);

    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        rev[B].push_back(A);   // edge A -> B, so A is reachable from B in reverse
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int C;
        cin >> C;

        vector<bool> visited(N + 1, false);
        queue<int> q;

        visited[C] = true;
        q.push(C);

        int count = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int prereq : rev[u]) {
                if (!visited[prereq]) {
                    visited[prereq] = true;
                    ++count;
                    q.push(prereq);
                }
            }
        }

        cout << count << '\n';
    }

    return 0;
}