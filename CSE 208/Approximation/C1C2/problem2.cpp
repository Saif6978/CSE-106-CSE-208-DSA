#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<pair<int, int>> edges(m);
    for (auto &e : edges) cin >> e.first >> e.second;

    // 1. 2-Approximation
    vector<bool> covered(m, false);
    vector<int> approx_cover;
    for (int i = 0; i < m; i++) {
        if (!covered[i]) {
            int u = edges[i].first;
            int v = edges[i].second;
            approx_cover.push_back(u);
            approx_cover.push_back(v);
            for (int j = i; j < m; j++) {
                if (edges[j].first == u || edges[j].second == u ||
                    edges[j].first == v || edges[j].second == v) {
                    covered[j] = true;
                }
            }
        }
    }
    sort(approx_cover.begin(), approx_cover.end());
    approx_cover.erase(unique(approx_cover.begin(), approx_cover.end()), approx_cover.end());

    // 2. Exact Optimal Vertex Cover via Brute Force (for n <= 25)
    vector<int> opt_cover;
    if (n <= 25) {
        int best_size = n + 1;
        int best_mask = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            int sz = __builtin_popcount(mask);
            if (sz >= best_size) continue;
            bool ok = true;
            for (const auto& e : edges) {
                if (!(mask & (1 << e.first)) && !(mask & (1 << e.second))) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                best_size = sz;
                best_mask = mask;
            }
        }
        for (int i = 0; i < n; i++) {
            if (best_mask & (1 << i)) opt_cover.push_back(i);
        }
    }

    cout << "--- 2-Approximation Solution ---\n";
    cout << "Size: " << approx_cover.size() << "\nVertices: ";
    for (int v : approx_cover) cout << v << " ";
    cout << "\n\n";

    if (n <= 25) {
        cout << "--- Optimal Solution (Brute Force) ---\n";
        cout << "Size: " << opt_cover.size() << "\nVertices: ";
        for (int v : opt_cover) cout << v << " ";
        cout << "\n\n";

        double ratio = (opt_cover.empty()) ? 1.0 : (double)approx_cover.size() / opt_cover.size();
        cout << "Approximation Ratio: " << fixed << setprecision(3) << ratio << "\n";
    }
    return 0;
}
