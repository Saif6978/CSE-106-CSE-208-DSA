#include <bits/stdc++.h>
using namespace std;

int main(){
    int N,M,K;
    cin>>N>>M>>K;
    vector<int> cap(N+1);
    vector<bool> blocked(N+1,false);
    for(int i=1;i<=N;i++){
        cin>>cap[i];
        if(cap[i]==-1) blocked[i]=true;
    }
    const long long INF=1e18;
    vector<vector<long long>> dist(N+1,vector<long long>(N+1,INF));
    for(int i=1;i<=N;i++){
        if(!blocked[i]) dist[i][i]=0;
    }
    for(int i=0;i<M;i++){
        int u,v,w;
        cin>>u>>v>>w;
        if(!blocked[u] && !blocked[v]){
            dist[u][v]=min(dist[u][v],(long long)w);
            dist[v][u]=min(dist[v][u],(long long)w);
        }
    }
    for(int k=1;k<=N;k++){
        if(blocked[k])
            continue;
        for(int i=1;i<=N;i++){
            if(dist[i][k]==INF) continue;
            for(int j=1;j<=N;j++){
                if(dist[k][j]!=INF && dist[i][j]>dist[i][k]+dist[k][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
        }
    }
    int Q;
    cin>>Q;
    while(Q--){
        int start;
        cin>>start;
        vector<int> remaining=cap;
        vector<long long> ans;
        for(int student=0;student<K;student++){
            long long best=INF;
            int chosen=-1;
            for(int lab=1;lab<=N;lab++){
                if(blocked[lab] || remaining[lab]==0) continue;
                if(dist[start][lab]<best){
                    best=dist[start][lab];
                    chosen=lab;
                }
                else if(dist[start][lab]==best && lab<chosen){
                    chosen=lab;
                }
            }
            if(chosen==-1){
                ans.push_back(-1);
            }
            else{
                ans.push_back(best);
                remaining[chosen]--;
            }
        }
        for(int i=0;i<K;i++){
            if(i) cout<<" ";
            cout<<ans[i];
        }
        cout<<"\n";
    }
    return 0;
}