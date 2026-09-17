#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

pair<long long, vector<int>> cross(vector<int>& arr, int l, int m, int r) {
    long long ls = LLONG_MIN;
    long long sum = 0;
    int st = m;
    for (int i = m; i >= l; i--) {
        sum += arr[i];
        if (sum > ls) {
            ls = sum;
            st = i;
        }
    }
    long long rs = LLONG_MIN;
    sum = 0;
    int end = m + 1;
    for (int i = m + 1; i <= r; i++) {
        sum += arr[i];
        if (sum > rs) {
            rs = sum;
            end = i;
        }
    }
    vector<int> combo(arr.begin() + st, arr.begin() + end + 1);
    return {ls + rs, combo};
}

pair<long long, vector<int>> gb(pair<long long, vector<int>> fr, pair<long long, vector<int>> sd) {
    if (fr.first > sd.first) return fr;
    if (fr.first < sd.first) return sd;
    if (fr.second.size() < sd.second.size()) return fr;
    if (fr.second.size() > sd.second.size()) return sd;
    return sd;
}

pair<long long, vector<int>> hot(vector<int>& arr, int l, int r) {
    if (l > r) return {0, {}};
    if (l == r) {
        return {arr[l], {arr[l]}};
    }
    int m = l + (r - l) / 2;
    auto left = hot(arr, l, m);
    auto right = hot(arr, m + 1, r);
    auto cr = cross(arr, l, m, r);
    return gb(gb(left, right), cr);
}

int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        cout << "[] with a sum 0" << endl;
        return 0;
    }
    vector<int> score(n);
    for (int i = 0; i < n; i++) {
        cin >> score[i];
    }
    auto res = hot(score, 0, n - 1);
    cout << "[";
    if (res.first <= 0) {
        cout << "] with a sum 0" << endl;
        return 0;
    }
    for (size_t i = 0; i < res.second.size(); i++) {
        cout << res.second[i];
        if (i + 1 < res.second.size()) {
            cout << ", ";
        }
    }
    cout << "] with a sum " << res.first << endl;
    return 0;
}
