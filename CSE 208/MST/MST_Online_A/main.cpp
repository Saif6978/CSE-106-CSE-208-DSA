#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    vector<int> d;
    BigInt() { d.push_back(1); }
    BigInt(long long v) {
        d.clear();
        if (v == 0) d.push_back(0);
        while (v > 0) {
            d.push_back(v % 10);
            v /= 10;
        }
    }
    void multiply(long long x) {
        long long carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            long long cur = (long long)d[i] * x + carry;
            d[i] = cur % 10;
            carry = cur / 10;
        }
        while (carry > 0) {
            d.push_back(carry % 10);
            carry /= 10;
        }
    }
    bool operator<(const BigInt& o) const {
        if (d.size() != o.d.size()) return d.size() < o.d.size();
        for (int i = (int)d.size() - 1; i >= 0; i--) {
            if (d[i] != o.d[i]) return d[i] < o.d[i];
        }
        return false;
    }
    bool operator>(const BigInt& o) const {
        return o < *this;
    }
    bool operator==(const BigInt& o) const {
        return d == o.d;
    }
    void print() const {
        for (int i = (int)d.size() - 1; i >= 0; i--) cout << d[i];
    }
};

struct Edge {
    int u, v;
    long long w;
    double lw;
    bool used = false;
};

struct DSU {
    vector<int> p;
    DSU(int n) {
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    }
};

BigInt productTree(const vector<Edge>& edges, const vector<int>& ids) {
    BigInt ans(1);
    for (int i : ids) ans.multiply(edges[i].w);
    return ans;
}

bool dfs(int u, int par, int target, const vector<vector<pair<int, int>>>& tree, vector<int>& path) {
    if (u == target) return true;
    for (auto [v, id] : tree[u]) {
        if (v == par) continue;
        path.push_back(id);
        if (dfs(v, u, target, tree, path)) return true;
        path.pop_back();
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].lw = log((double)edges[i].w);
    }
    vector<int> order(M);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (edges[a].lw == edges[b].lw) return edges[a].w < edges[b].w;
        return edges[a].lw < edges[b].lw;
    });

    DSU dsu(N);
    vector<vector<pair<int, int>>> tree(N + 1);
    vector<int> mst;
    for (int id : order) {
        if (dsu.unite(edges[id].u, edges[id].v)) {
            edges[id].used = true;
            mst.push_back(id);
            tree[edges[id].u].push_back({edges[id].v, id});
            tree[edges[id].v].push_back({edges[id].u, id});
        }
    }
    if ((int)mst.size() != N - 1) {
        cout << -1;
        return 0;
    }

    BigInt mstProduct = productTree(edges, mst);
    bool foundAnswer = false;
    BigInt answer;

    for (int id = 0; id < M; id++) {
        if (edges[id].used) continue;
        vector<int> path;
        dfs(edges[id].u, -1, edges[id].v, tree, path);
        for (int removeEdge : path) {
            vector<int> candidate;
            for (int x : mst) {
                if (x != removeEdge) candidate.push_back(x);
            }
            candidate.push_back(id);
            BigInt val = productTree(edges, candidate);
            if (val > mstProduct && (!foundAnswer || val < answer)) {
                answer = val;
                foundAnswer = true;
            }
        }
    }

    if (!foundAnswer) cout << -1;
    else answer.print();
    return 0;
}