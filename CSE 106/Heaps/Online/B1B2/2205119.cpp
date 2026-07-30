#include "MaxHeap.h"
using namespace std;
int main(){
    MaxHeap heap;
    int number_of_bags,minutes;
    cin >> number_of_bags >> minutes;
    for(int i=0;i<number_of_bags;i++){
        int candies;
        cin >> candies;
        heap.insert(candies);
    }
    int sum=0;
    for(int i=0;i<minutes;i++){
        int x=heap.extractMax();
        sum+=x;
        heap.insert(x/2);
    }
    cout << sum << endl;
    return 0;
}
