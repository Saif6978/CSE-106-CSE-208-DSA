#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.assign(n, 0);

        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if(a == b)
            return false;

        if(rankv[a] < rankv[b])
            swap(a,b);

        parent[b] = a;

        if(rankv[a] == rankv[b])
            rankv[a]++;

        return true;
    }
};


struct Edge {
    int u,v;
    long long w;
    long long cost;
};


int main() {

    int N,M;
    long long P;

    cin >> N >> M >> P;


    int K;
    cin >> K;


    vector<int> risky(N,0);

    for(int i=0;i<K;i++){
        int x;
        cin >> x;
        risky[x]=1;
    }


    vector<Edge> safeEdges;
    vector<Edge> allEdges;


    for(int i=0;i<M;i++){

        int u,v;
        long long w;

        cin >> u >> v >> w;


        long long penalty = 0;

        if(risky[u])
            penalty += P;

        if(risky[v])
            penalty += P;


        Edge e;

        e.u=u;
        e.v=v;
        e.w=w;
        e.cost=w+penalty;


        allEdges.push_back(e);


        if(!risky[u] && !risky[v])
            safeEdges.push_back(e);
    }


    DSU dsu(N);

    vector<Edge> answer;

    long long total=0;



    // Phase 1:
    // Use only safe city connections

    sort(
        safeEdges.begin(),
        safeEdges.end(),
        [](Edge a, Edge b){
            return a.w < b.w;
        }
    );


    for(auto e:safeEdges){

        if(dsu.unite(e.u,e.v)){

            answer.push_back(e);
            total += e.cost;
        }
    }



    auto connectedSafe = [&]() {

        int root=-1;

        for(int i=0;i<N;i++){

            if(!risky[i]){

                if(root==-1)
                    root=dsu.find(i);

                else if(root!=dsu.find(i))
                    return false;
            }
        }

        return true;
    };



    // Phase 2:
    // Add risky edges only if necessary

    if(!connectedSafe()){

        sort(
            allEdges.begin(),
            allEdges.end(),
            [](Edge a, Edge b){
                return a.cost < b.cost;
            }
        );


        for(auto e:allEdges){

            if(dsu.unite(e.u,e.v)){

                answer.push_back(e);
                total += e.cost;

                if(connectedSafe())
                    break;
            }
        }
    }



    if(!connectedSafe()){

        cout << -1 << endl;
        return 0;
    }



    cout << answer.size() << endl;


    for(auto e:answer){

        cout << e.u << " "
             << e.v << endl;
    }


    cout << total << endl;


    return 0;
}
