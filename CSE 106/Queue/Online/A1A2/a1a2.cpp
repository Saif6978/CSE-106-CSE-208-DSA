#include "QueueLinkedList.h"
#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;  // number of test cases

    while (T--) {
        int n;
        cin >> n;

        Queue firstHalf, secondHalf;
        int mid = n / 2;

        // Read all n numbers and enqueue into appropriate halves
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (i < mid)
                firstHalf.enqueue(x);
            else
                secondHalf.enqueue(x);
        }

        // Interleave and print
        while (!firstHalf.isEmpty() && !secondHalf.isEmpty()) {
            cout << firstHalf.dequeue() << " ";
            cout << secondHalf.dequeue() << " ";
        }
        // If odd length (not in sample), firstHalf would have one extra element
        while (!firstHalf.isEmpty()) {
            cout << firstHalf.dequeue() << " ";
        }
        while (!secondHalf.isEmpty()) {
            cout << secondHalf.dequeue() << " ";
        }
        cout << endl;
    }
    return 0;
}