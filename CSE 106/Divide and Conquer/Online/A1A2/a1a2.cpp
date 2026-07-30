#include <iostream>
#include <string>
using namespace std;

int countAdjacentInverted(const string& s, int l, int r) {
    if (l >= r) return 0;                      // no pairs
    if (l + 1 == r) {                          // exactly one pair
        return (s[l] > s[r]) ? 1 : 0;
    }
    int mid = l + (r - l) / 2;
    int left = countAdjacentInverted(s, l, mid);
    int right = countAdjacentInverted(s, mid + 1, r);
    int cross = (s[mid] > s[mid + 1]) ? 1 : 0; // boundary pair
    return left + right + cross;
}

int main() {
    string s;
    cin >> s;                                  // read the string
    int n = (int)s.size();
    int ans = countAdjacentInverted(s, 0, n - 1);
    cout << ans << endl;
    return 0;
}