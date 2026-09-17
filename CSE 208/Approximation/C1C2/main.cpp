#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<pair<int, int>> edges(m);
    for (auto &e : edges) cin >> e.first >> e.second;

    vector<bool> covered(m, false);
    vector<int> cover;

    for (int i = 0; i < m; i++) {
        if (!covered[i]) {
            int u = edges[i].first;
            int v = edges[i].second;
            cover.push_back(u);
            cover.push_back(v);
            for (int j = i; j < m; j++) {
                if (edges[j].first == u || edges[j].second == u ||
                    edges[j].first == v || edges[j].second == v) {
                    covered[j] = true;
                }
            }
        }
    }

    sort(cover.begin(), cover.end());
    cover.erase(unique(cover.begin(), cover.end()), cover.end());

    cout << cover.size() << "\n";
    for (size_t i = 0; i < cover.size(); i++) {
        cout << cover[i] << (i + 1 == cover.size() ? "" : " ");
    }
    cout << "\n";
    return 0;
}