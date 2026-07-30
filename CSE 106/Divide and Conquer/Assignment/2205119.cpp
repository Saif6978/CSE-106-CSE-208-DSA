#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
pair<long long,vector<int>> cross(vector<int>& arr,int l,int m,int r){
    long long ls=INT_MIN;
    long long sum=0;
    long long st=m;
    for(int i=m;i>=l;i--){
        sum+=arr[i];
        if(sum>ls){
            ls=sum;
            st=i;
        }
    }
    long long rs=INT_MIN;
    sum=0;
    int end=m+1;
    for(int i=m+1;i<=r;i++){
        sum+=arr[i];
        if(sum>rs){
            rs=sum;
            end=i;
        }
    }
    vector<int> combo(arr.begin()+st,arr.begin()+end+1);
    return {ls+rs,combo};
}
pair<long long,vector<int>> gb(pair<long long,vector<int>> fr,pair<long long,vector<int>> sd){
    if(fr.first>sd.first)return fr;
    if(fr.first<sd.first)return sd;
    if(fr.second.size()<sd.second.size())return fr;
    if(fr.second.size()>sd.second.size())return sd;
    return sd;
}
pair<long long,vector<int>> hot(vector<int>& arr,int l,int r){
    if(l==r){
        return {arr[l],{arr[l]}};
    }
    int m=l+(r-l)/2;
    auto left=hot(arr,l,m);
    auto right=hot(arr,m+1,r);
    auto cr=cross(arr,l,m,r);
    return gb(gb(left,right),cr);
}
int main(){
    int n;
    cin >> n;
    vector<int> score(n);
    for(int i=0;i<n;i++){
        cin >> score[i];
    }
    auto res=hot(score,0,n-1);
    cout << "[";
    if(res.first<=0){
        cout << "] with a sum " << "0" << endl;
        return 0;
    }
    for(int i=0;i<res.second.size();i++){
        cout << res.second[i];
        if(i<res.second.size()-1){
            cout <<", ";
        }
    }
    cout << "] with a sum " << res.first << endl;
    return 0;
}
