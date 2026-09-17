#include <iostream>
#include "StackUsingQueue.h"
using namespace std;

bool palindrome(Queue que) {
    Stack st;
    int n = que.length();
    for (int i = 0; i < n; i++) {
        st.push(que.peek());
        que.enqueue(que.peek());
        que.dequeue();
    }
    while (!que.isEmpty()) {
        if (st.top() != que.peek()) {
            return false;
        }
        que.dequeue();
        st.pop();
    }
    return true;
}

int main() {
    int x;
    if (!(cin >> x)) return 0;
    Queue que;
    while (x--) {
        char p;
        cin >> p;
        que.enqueue(p);
    }
    if (palindrome(que)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    return 0;
}
