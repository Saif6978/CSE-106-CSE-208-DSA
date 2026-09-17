#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.assign(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if(a == b) return false;

        if(rankv[a] < rankv[b])
            swap(a, b);

        parent[b] = a;

        if(rankv[a] == rankv[b])
            rankv[a]++;

        return true;
    }
};

struct Edge {
    int u, v;
    double w;
    bool road;
};

int main() {
    int n;
    double r;

    cin >> n >> r;

    vector<pair<double,double>> city(n);

    for(int i = 0; i < n; i++)
        cin >> city[i].first >> city[i].second;

    vector<Edge> edges;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {

            double dx = city[i].first - city[j].first;
            double dy = city[i].second - city[j].second;

            double dist = sqrt(dx*dx + dy*dy);

            edges.push_back({
                i,
                j,
                dist,
                dist <= r
            });
        }
    }

    sort(edges.begin(), edges.end(),
    [](Edge a, Edge b) {
        return a.w < b.w;
    });

    DSU dsu(n);

    double road = 0;
    double rail = 0;

    int railEdges = 0;
    int count = 0;

    for(auto e : edges) {

        if(dsu.unite(e.u, e.v)) {

            count++;

            if(e.road)
                road += e.w;
            else {
                rail += e.w;
                railEdges++;
            }

            if(count == n-1)
                break;
        }
    }

    cout << railEdges + 1 << " "
         << (long long)round(road) << " "
         << (long long)round(rail) << endl;

    return 0;
}
