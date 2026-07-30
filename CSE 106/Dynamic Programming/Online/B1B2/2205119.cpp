#include<iostream>
#include<vector>
#include<string>

using namespace std;

int match(string& s,string& d,int i,int j,vector<vector<int>>& arr){
    if(i<0 && j<0)return 0;
    if(i>=0 && j<0)return i+1;
    if(i<0 && j>=0)return j+1;
    if(arr[i][j]!=-1)return arr[i][j];
    if(s[i]==d[j]){
        return arr[i][j]=match(s,d,i-1,j-1,arr);
    }
    if(s[i]!=d[j]){
        return arr[i][j]=1+min(min(match(s,d,i,j-1,arr),match(s,d,i-1,j,arr)),match(s,d,i-1,j-1,arr));//remove insert replace
    }
    return arr[i][j];
}

int mis(string& a,string& b){
    int m=a.size();
    int n=b.size();
    vector<vector<int>> dp(m,vector<int>(n,-1));
    return match(a,b,m-1,n-1,dp);
}
int main(){
    string a,b;
    getline(cin,a);
    getline(cin,b);
    cout << mis(a,b) << endl;
    return 0;
}
