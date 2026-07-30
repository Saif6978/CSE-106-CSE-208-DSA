#include <iostream>
#include "StackUsingQueue.h"   // Implicitly includes QueueLinkedList.h

using namespace std;

int main() {
    Queue q;        // The queue to be sorted
    int x;

    // Read all integers from standard input into the queue
    while (cin >> x) {
        q.enqueue(x);
    }

    Stack s;        // Only one stack allowed

    // Sort the queue using the stack
    while (!q.isEmpty()) {
        int current = q.dequeue();

        // Pop from stack while top is smaller than current
        // and push those elements back to the queue
        while (!s.isEmpty() && s.top() < current) {
            q.enqueue(s.pop());
        }
        s.push(current);
    }

    // Transfer all elements from stack to queue (now sorted ascending)
    while (!s.isEmpty()) {
        q.enqueue(s.pop());
    }

    // Output the sorted queue
    bool first = true;
    while (!q.isEmpty()) {
        if (!first) cout << " ";
        cout << q.dequeue();
        first = false;
    }
    cout << endl;

    return 0;
}