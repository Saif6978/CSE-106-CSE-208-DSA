#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    vector<int> value(n), weight(n);
    for (int i = 0; i < n; i++) cin >> value[i];
    for (int i = 0; i < n; i++) cin >> weight[i];
    // dp[i][j] = maximum value using first i houses (0..i-1) with capacity j
    vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            // Option 1: do not rob house i-1
            dp[i][j] = dp[i - 1][j];
            // Option 2: rob house i-1 (if weight allows)
            if (weight[i - 1] <= j) {
                if (i == 1) {
                    // Only one house, no previous to worry about
                    dp[i][j] = max(dp[i][j], value[i - 1]);
                } else {
                    // If we rob i-1, we cannot rob i-2, so use dp[i-2]
                    dp[i][j] = max(dp[i][j],
                    dp[i - 2][j - weight[i - 1]] + value[i - 1]);
                }
            }
        }
    }
    cout << dp[n][w] << endl;
    return 0;
}