#include<bits/stdc++.h>
#include "2205119.h"
using namespace std;
int main() {
    Bino_Heap heap;
    while (1) {
        char c;
        cin >> c;
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
        else{
            break;
        }
    }
    return 0;
}
