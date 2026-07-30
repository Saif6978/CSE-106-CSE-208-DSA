#include <iostream>
#include <vector>
using namespace std;

long long merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;
    long long inv = 0;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // arr[i] > arr[j], all from i to m are greater than arr[j]
            inv += (m - i + 1);
            temp[k++] = arr[j++];
        }
    }

    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (int p = 0; p < k; p++) {
        arr[l + p] = temp[p];
    }

    return inv;
}

long long countInversions(vector<int>& arr, int l, int r) {
    if (l >= r) return 0;

    int m = l + (r - l) / 2;
    long long left = countInversions(arr, l, m);
    long long right = countInversions(arr, m + 1, r);
    long long cross = merge(arr, l, m, r);

    return left + right + cross;
}

int main() {
    int n;
    cin >> n;                           // read size of array
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    long long ans = countInversions(arr, 0, n - 1);
    cout << ans << endl;

    return 0;
}