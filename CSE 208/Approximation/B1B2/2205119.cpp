#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, capacity;
    double eps;
    if (!(cin >> n >> capacity >> eps)) return 0;
    if (n <= 0) {
        cout << 0 << "\n\n";
        return 0;
    }

    vector<int> w(n), v(n);
    int vmax = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
        vmax = max(vmax, v[i]);
    }

    if (vmax == 0 || eps <= 0) {
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (w[i] <= capacity) {
                ans.push_back(i);
                break;
            }
        }
        cout << 0 << "\n";
        for (int x : ans) cout << x << " ";
        cout << "\n";
        return 0;
    }

    double K = (eps * vmax) / n;
    vector<int> scaled(n);
    int total = 0;
    for (int i = 0; i < n; i++) {
        scaled[i] = (int)floor(v[i] / K);
        total += scaled[i];
    }

    const int INF = 1e9 + 7;
    vector<int> dp(total + 1, INF);
    vector<vector<int>> take(n + 1, vector<int>(total + 1, 0));
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        vector<int> ndp = dp;
        for (int j = 0; j <= total; j++) {
            if (dp[j] != INF && dp[j] + w[i] <= capacity && j + scaled[i] <= total) {
                if (dp[j] + w[i] < ndp[j + scaled[i]]) {
                    ndp[j + scaled[i]] = dp[j] + w[i];
                    take[i + 1][j + scaled[i]] = 1;
                }
            }
        }
        dp = ndp;
    }

    int best = 0;
    for (int i = 0; i <= total; i++) {
        if (dp[i] <= capacity) best = i;
    }

    vector<int> ans;
    int cur = best;
    for (int i = n; i >= 1; i--) {
        if (take[i][cur]) {
            ans.push_back(i - 1);
            cur -= scaled[i - 1];
        }
    }
    reverse(ans.begin(), ans.end());

    int value = 0;
    for (int i : ans) value += v[i];
    cout << value << "\n";
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] << (i + 1 == ans.size() ? "" : " ");
    }
    cout << "\n";
    return 0;
}