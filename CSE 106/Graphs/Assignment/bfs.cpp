#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
void bfs(vector<vector<int>>& graph,vector<int>& arr,int vertex){
    queue <int> que;
    que.push(vertex);
    arr[vertex]=1;
    while(!que.empty()){
        int curr=que.front();
        que.pop();
        for(int i=1;i<arr.size();i++){
            if(arr[i]==0 && graph[curr][i]==1){
                arr[i]=1;
                que.push(i);
            }
        }
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<int> arr(n+1,0);
    vector<vector<int>> graph1(n+1,vector<int>(n+1,0));
    for(int v=0;v<m;v++){
        int a,b;
        cin >> a >> b;
        graph1[a][b]=1;
        graph1[b][a]=1;
    }
    queue<int> que;
    for(int i=1;i<=n;i++){
        if(arr[i]==0){
            que.push(i);
            bfs(graph1,arr,i);
        }
    }
    cout << que.size()-1 << endl;
    int c=que.front();
    que.pop();
    while(!que.empty()){
        cout << c << " " << que.front() << endl;
        c=que.front();
        que.pop();
    }
    /*for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << graph1[i][j] << " ";
        }
        cout << endl;
    }*/
    return 0;
}
