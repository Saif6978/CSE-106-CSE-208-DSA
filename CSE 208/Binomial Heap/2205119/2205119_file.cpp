#include<bits/stdc++.h>
#include "2205119.h"
using namespace std;
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Bino_Heap heap;
    char c;
    while (cin >> c) {
        if (c=='I' || c=='i') {
            int x;
            cin >> x;
            heap.Insert(x);
        }
        else if (c=='D' || c=='d') {
            int a,b;
            cin >> a >> b;
            heap.Update_Key(a,b);
        }
        else if (c=='F' || c=='f') {
            Node* m = heap.Find_Min();
            if (m) cout << "Find Min returned: " << m->data << endl;
            else cout << "Heap is empty" << endl;
        }
        else if (c=='E' || c=='e') {
            int ext = heap.Extract_Min();
            if (ext != -1) cout << "Extract Min returned: " << ext << endl;
            else cout << "Heap is empty" << endl;
        }
        else if (c=='R' || c=='r') {
            int x;
            cin >> x;
            heap.Remove_Key(x);
        }
        else if (c=='P' || c=='p') {
            heap.Print();
        }
    }
    return 0;
}
