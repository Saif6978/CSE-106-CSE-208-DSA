#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
void sol(vector<int>& arr,int l,int h,int& a){
    if(l>=h){
        return;
    }
    int m=l+(h-l)/2;

    sol(arr,l,m,a);
    sol(arr,m+1,h,a);

    if(arr[m]==arr[m+1]){
        a++;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    int a=0;
    sol(arr,0,n-1,a);
    cout << n-a << endl;
    return 0;
}
