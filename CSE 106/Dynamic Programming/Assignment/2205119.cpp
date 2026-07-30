#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool matcher(string& s,string& d,int a,int b,vector<vector<int>>& arr){
    if(a<0 && b<0){
        return true;
    }
    if(a>=0 && b<0){
        return false;
    }
    if(a<0 && b>=0){
        if(d[b]=='*')return matcher(s,d,a,b-2,arr);
        return false;
    }
    if(arr[a][b]!=-1){
        return arr[a][b];
    }
    if(s[a] == d[b] || d[b] == '.') {
        return arr[a][b]=matcher(s,d,a-1,b-1,arr);
    }
    if(d[b] == '*') {
        if(b>0 && (s[a] == d[b-1] || d[b-1] == '.')) {
            return arr[a][b]=matcher(s,d,a-1,b,arr) || matcher(s,d,a,b-2,arr);
        }
        return arr[a][b]=matcher(s,d,a,b-2,arr);
    }
    if (d[b] == '+') {
        if (b>0 && (s[a] == d[b-1] || d[b-1] == '.')) {
            return arr[a][b]=matcher(s,d,a-1,b,arr) || matcher(s,d,a,b-1,arr);
        }
        return arr[a][b]=false;
    }
    return arr[a][b]=false;
}

bool sol(string& s,string& d){
    vector<vector<int>> arr(s.size(),vector<int>(d.size(),-1));
    return matcher(s,d,s.size()-1,d.size()-1,arr);
}

int main(){
    string s,d;
    getline(cin,s);
    getline(cin,d);
    if(sol(s,d)){
        cout << "True" << endl;
    }
    else{
        cout << "False" << endl;
    }
    return 0;
}
