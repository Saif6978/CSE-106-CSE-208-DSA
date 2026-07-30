#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
void dfs(vector<int> graph[],vector<int>& arr,int vertex){
    //action on vertex after entering vertex
    arr[vertex]=1;
    for(int it:graph[vertex]){
        if(arr[it]==1)continue;
        //action on child before entering
        dfs(graph,arr,it);
        //action on child after exiting
    }
    //action on vertex before exiting
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<int> arr(n+1,0);
    vector<int>graph2[n+1];
    for(int v=0;v<m;v++){
        int a,b;
        cin >> a >> b;
        graph2[a].push_back(b);
        graph2[b].push_back(a);
    }
    stack<int>st;
    for(int i=1;i<=n;i++){
        if(arr[i]==0){
            st.push(i);
            dfs(graph2,arr,i);
        }
    }
    cout << st.size()-1 << endl;
    int c=st.top();
    st.pop();
    while(!st.empty()){
        cout << c << " " << st.top() << endl;
        c=st.top();
        st.pop();
    }
    /*for(int i=0;i<n;i++){
        for(int j=0;j<graph2[i].size();j++){
            cout << i << ": " << graph2[i][j] << " ";
        }
        cout << endl;
    }*/
    return 0;
}
