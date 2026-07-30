#include "MaxHeap.h"
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    MaxHeap heap;

    // Insert all rows' initial empty seat counts
    for (int i = 0; i < M; ++i) {
        int seats;
        cin >> seats;
        heap.insert(seats);
    }

    long long totalRevenue = 0;

    // Sell tickets to each fan
    for (int i = 0; i < N; ++i) {
        // If no seats left, stop (though N should be ≤ total seats)
        if (heap.isEmpty())
            break;

        int maxSeats = heap.extractMax();  // current highest price
        totalRevenue += maxSeats;

        // One seat sold – decrease count
        maxSeats--;
        if (maxSeats > 0) {
            heap.insert(maxSeats);        // reinsert if still available
        }
    }

    cout << totalRevenue << '\n';
    return 0;
}