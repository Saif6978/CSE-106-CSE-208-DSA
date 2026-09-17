#include <bits/stdc++.h>
using namespace std;

struct Slot {
    int id = -1;
    int state = 0; // 0 empty, 1 occupied, 2 deleted
};

bool isPrime(int x) {
    if (x < 2) return false;
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int nextPrime(int x) {
    while (!isPrime(x)) x++;
    return x;
}

class MemoryManager {
    vector<Slot> table;
    int initial, pmax, sz;
    int delCount = 0;
    int maxProbe = 0;

    int hashFunc(int x) const {
        return (x % sz + sz) % sz;
    }

    void reportBefore() {
        int active = 0;
        for (const auto& s : table) {
            if (s.state == 1) active++;
        }
        cout << "--- Rehash Triggered: BEFORE ---\n";
        cout << "Table Size: " << sz << "\n";
        cout << "Active Processes: " << active << "\n";
        cout << "Load Factor: " << fixed << setprecision(2) << (double)active / sz << "\n";
        cout << "Max Probe Sequence: " << maxProbe << "\n";
    }

    void rehash(int newSize) {
        vector<int> activeProcesses;
        for (const auto& s : table) {
            if (s.state == 1) activeProcesses.push_back(s.id);
        }

        table.assign(newSize, Slot());
        sz = newSize;
        int rehashMaxProbe = 0;
        delCount = 0;

        for (int pid : activeProcesses) {
            auto [idx, probes] = findSlot(pid);
            table[idx] = {pid, 1};
            rehashMaxProbe = max(rehashMaxProbe, probes);
        }

        int active = (int)activeProcesses.size();
        cout << "--- Rehash Triggered: AFTER ---\n";
        cout << "Table Size: " << sz << "\n";
        cout << "Active Processes: " << active << "\n";
        cout << "Load Factor: " << fixed << setprecision(2) << (double)active / sz << "\n";
        cout << "Max Probe Sequence: " << rehashMaxProbe << "\n";
        maxProbe = 0;
    }

    pair<int, int> findSlot(int x) const {
        int h = hashFunc(x);
        for (int i = 0; i < sz; i++) {
            int idx = (h + (long long)i * i) % sz;
            if (table[idx].state != 1) {
                return {idx, i + 1};
            }
        }
        return {-1, sz + 1};
    }

public:
    MemoryManager(int n, int p) : initial(n), pmax(p), sz(n) {
        table.resize(n);
    }

    void allocate(int x) {
        auto [idx, probes] = findSlot(x);
        while (probes > pmax) {
            reportBefore();
            rehash(nextPrime(sz * 2));
            auto res = findSlot(x);
            idx = res.first;
            probes = res.second;
        }
        table[idx] = {x, 1};
        maxProbe = max(maxProbe, probes);
        cout << "ALLOCATE " << x << ": Inserted at index " << idx << " (probes: " << probes << ")\n";
    }

    void freeProcess(int x) {
        int h = hashFunc(x);
        for (int i = 0; i < sz; i++) {
            int idx = (h + (long long)i * i) % sz;
            if (table[idx].state == 0) break;
            if (table[idx].state == 1 && table[idx].id == x) {
                table[idx].state = 2;
                cout << "FREE " << x << ": Freed from index " << idx << "\n";
                delCount++;
                if (delCount % 5 == 0) {
                    int active = 0;
                    for (const auto& s : table) {
                        if (s.state == 1) active++;
                    }
                    if ((double)active / sz < 0.2) {
                        int target = sz / 2;
                        while (target > 0 && !isPrime(target)) target--;
                        if (target >= initial) {
                            reportBefore();
                            rehash(target);
                        }
                    }
                }
                return;
            }
        }
        cout << "FREE " << x << ": Not found\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p, q;
    if (!(cin >> n >> p >> q)) return 0;
    MemoryManager mm(n, p);
    while (q--) {
        string op;
        int x;
        if (!(cin >> op >> x)) break;
        if (op == "ALLOCATE") mm.allocate(x);
        else mm.freeProcess(x);
    }
    return 0;
}
