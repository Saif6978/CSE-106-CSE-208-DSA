#include "MaxHeap.h"
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    MaxHeap heap;          // your heap object (initial size = 0)

    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        heap.insert(x);    // O(log n)

        if (heap.getSize() < 3) {
            cout << -1 << '\n';
        } else {
            // Extract the three largest (they are removed from heap)
            int first  = heap.extractMax();
            int second = heap.extractMax();
            int third  = heap.extractMax();

            long long product = 1LL * first * second * third;
            cout << product << '\n';

            // Reinsert them to restore the heap for the next prefix
            heap.insert(first);
            heap.insert(second);
            heap.insert(third);
        }
    }

    return 0;
}