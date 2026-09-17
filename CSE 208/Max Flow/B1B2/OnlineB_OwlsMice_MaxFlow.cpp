#include <bits/stdc++.h>
using namespace std;

int cap[205][205], parentNode[205];
bool visited[205];

bool bfs(int s,int t,int n){
    memset(visited,false,sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s]=true;
    parentNode[s]=-1;

    while(!q.empty()){
        int u=q.front();
        q.pop();

        for(int v=0;v<n;v++){
            if(!visited[v] && cap[u][v]>0){
                visited[v]=true;
                parentNode[v]=u;
                q.push(v);
            }
        }
    }
    return visited[t];
}

int maxFlow(int s,int t,int n){
    int flow=0;

    while(bfs(s,t,n)){
        int path=INT_MAX;

        for(int v=t;v!=s;v=parentNode[v])
            path=min(path,cap[parentNode[v]][v]);

        for(int v=t;v!=s;v=parentNode[v]){
            int u=parentNode[v];
            cap[u][v]-=path;
            cap[v][u]+=path;
        }

        flow+=path;
    }
    return flow;
}

int main(){
    int T;
    cin>>T;

    for(int tc=1;tc<=T;tc++){
        int M,H;
        double R;
        cin>>M>>H>>R;

        vector<double> mx(M),my(M);
        vector<double> hx(H),hy(H);
        vector<int> hc(H);

        for(int i=0;i<M;i++)
            cin>>mx[i]>>my[i];

        for(int i=0;i<H;i++)
            cin>>hx[i]>>hy[i]>>hc[i];

        memset(cap,0,sizeof(cap));

        int source=0;
        int mouseStart=1;
        int holeStart=1+M;
        int sink=M+H+1;
        int nodes=sink+1;

        for(int i=0;i<M;i++)
            cap[source][mouseStart+i]=1;

        for(int i=0;i<M;i++){
            for(int j=0;j<H;j++){
                double d=sqrt(
                    (mx[i]-hx[j])*(mx[i]-hx[j])+
                    (my[i]-hy[j])*(my[i]-hy[j])
                );

                if(d<=R)
                    cap[mouseStart+i][holeStart+j]=1;
            }
        }

        for(int i=0;i<H;i++)
            cap[holeStart+i][sink]=hc[i];

        cout<<"Case "<<tc<<": "<<maxFlow(source,sink,nodes)<<"\n";
    }
}
