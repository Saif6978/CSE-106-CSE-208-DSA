#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
bool bfs(vector<vector<char>>& graph,vector<vector<int>>& arr,int a,int b){
    if(arr[a][b]==1 || graph[a][b]=='#')return false;
    else if(graph[a][b]=='S'){
        return true;
    }
    arr[a][b]=1;
    if(a==graph.size()-1){
        if(b==graph[a].size()-1){
            return bfs(graph,arr,a-1,b)|| bfs(graph,arr,a,b-1);
        }
        else if(b==0){
            return bfs(graph,arr,a-1,b)|| bfs(graph,arr,a,b+1);
        }
        else{
            return bfs(graph,arr,a-1,b)|| bfs(graph,arr,a,b+1) || bfs(graph,arr,a,b-1);
        }
    }
    else if(a==0){
        if(b==graph[a].size()-1){
            return bfs(graph,arr,a+1,b)|| bfs(graph,arr,a,b-1);
        }
        else if(b==0){
            return bfs(graph,arr,a+1,b)|| bfs(graph,arr,a,b+1);
        }
        else{
            return bfs(graph,arr,a+1,b)|| bfs(graph,arr,a,b+1) || bfs(graph,arr,a,b-1);
        }
    }
    else{
        if(b==graph[a].size()-1){
            return bfs(graph,arr,a-1,b)|| bfs(graph,arr,a,b-1) || bfs(graph,arr,a+1,b);
        }
        else if(b==0){
            return bfs(graph,arr,a-1,b)|| bfs(graph,arr,a,b+1) || bfs(graph,arr,a+1,b);
        }
        else{
            return bfs(graph,arr,a-1,b)|| bfs(graph,arr,a,b+1) || bfs(graph,arr,a,b-1) || bfs(graph,arr,a+1,b);
        }
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<char> arr(n,0);
    int a,b;
    vector<pair<int,int>>exits;
    vector<vector<char>> graph1(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> graph1[i][j];
            if(graph1[i][j]=='S'){
                a=i;
                b=j;
            }
            if(graph1[i][j]=='E'){
                exits.push_back({i,j});
            }
        }
    }
    int counter=0;
    for(int i=0;i<exits.size();i++){
        vector<vector<int>> graph2(n,vector<int>(m,0));
        if(bfs(graph1,graph2,exits[i].first,exits[i].second)){
           counter++;
        }
    }
    cout << counter << endl;
    /*for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << graph1[i][j] << " ";
        }
        cout << endl;
    }*/
    return 0;
}
