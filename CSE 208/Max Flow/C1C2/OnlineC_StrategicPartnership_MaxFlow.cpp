#include <bits/stdc++.h>
using namespace std;

struct Person{
    int exp,age,crime,origin,weapon,trust,lang;
};

vector<vector<int>> g;
vector<int> matchR,vis;

bool dfs(int u){
    for(int v:g[u]){
        if(!vis[v]){
            vis[v]=1;
            if(matchR[v]==-1 || dfs(matchR[v])){
                matchR[v]=u;
                return true;
            }
        }
    }
    return false;
}

bool valid(Person a,Person b){
    if(abs(a.exp-b.exp)>12) return false;
    if(abs(a.age-b.age)>5) return false;
    if(a.crime!=b.crime) return false;
    if(a.origin!=b.origin) return false;
    if(!a.weapon && !b.weapon) return false;
    if(a.trust+b.trust<10) return false;
    if((a.lang&b.lang)==0) return false;
    return true;
}

int main(){
    int T;
    cin>>T;

    for(int tc=1;tc<=T;tc++){
        int m,n;
        cin>>m>>n;

        vector<Person>a(m),b(n);

        for(auto &x:a)
            cin>>x.exp>>x.age>>x.crime>>x.origin>>x.weapon>>x.trust>>x.lang;

        for(auto &x:b)
            cin>>x.exp>>x.age>>x.crime>>x.origin>>x.weapon>>x.trust>>x.lang;

        g.assign(m,{});

        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                if(valid(a[i],b[j]))
                    g[i].push_back(j);

        matchR.assign(n,-1);

        int ans=0;

        for(int i=0;i<m;i++){
            vis.assign(n,0);
            if(dfs(i))
                ans++;
        }

        cout<<"Case "<<tc<<": "<<ans<<"\n";
    }
}
