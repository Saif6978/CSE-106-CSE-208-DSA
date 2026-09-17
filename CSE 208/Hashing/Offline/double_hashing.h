#include <bits/stdc++.h>
using namespace std;

class D_Entry {
public:
    string key;
    int value;
    bool deleted;
    D_Entry() {
        key = "";
        value = -1;
        deleted = false;
    }
};

class DoubleHashing {
    vector<D_Entry> table;
    int tablesize;
    int (*hash1)(const string&, int);
    int (*hash2)(const string&, int);

public:
    int collisions = 0;

    DoubleHashing(int size, int (*h1)(const string&, int), int (*h2)(const string&, int)) {
        tablesize = size;
        hash1 = h1;
        hash2 = h2;
        collisions = 0;
        table.resize(tablesize);
    }

    bool insert(const string& key, int value) {
        int idx1 = hash1(key, tablesize);
        int idx2 = hash2(key, tablesize);
        int first_deleted = -1;
        int probes = 0;
        for (int i = 0; i < tablesize; i++) {
            probes++;
            int idx = (idx1 + 1LL * i * idx2) % tablesize;
            if (table[idx].deleted) {
                if (first_deleted == -1) first_deleted = idx;
            } else if (table[idx].key.empty()) {
                int target = (first_deleted != -1) ? first_deleted : idx;
                table[target].key = key;
                table[target].value = value;
                table[target].deleted = false;
                if (probes > 1) collisions += (probes - 1);
                return true;
            } else if (table[idx].key == key) {
                return false;
            }
        }
        if (first_deleted != -1) {
            table[first_deleted].key = key;
            table[first_deleted].value = value;
            table[first_deleted].deleted = false;
            if (probes > 1) collisions += (probes - 1);
            return true;
        }
        return false;
    }

    bool search(const string& key, int* probes = nullptr, double* time_ns = nullptr) {
        int idx1 = hash1(key, tablesize);
        int idx2 = hash2(key, tablesize);
        int probeCount = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < tablesize; i++) {
            probeCount++;
            int idx = (idx1 + 1LL * i * idx2) % tablesize;
            if (table[idx].key.empty() && !table[idx].deleted) break;
            if (table[idx].key == key && !table[idx].deleted) {
                if (probes) *probes = probeCount;
                auto end = std::chrono::high_resolution_clock::now();
                if (time_ns) *time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                return true;
            }
        }
        if (probes) *probes = probeCount;
        auto end = std::chrono::high_resolution_clock::now();
        if (time_ns) *time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        return false;
    }

    bool erase(const string& key) {
        int idx1 = hash1(key, tablesize);
        int idx2 = hash2(key, tablesize);
        for (int i = 0; i < tablesize; i++) {
            int idx = (idx1 + 1LL * i * idx2) % tablesize;
            if (table[idx].key.empty() && !table[idx].deleted) break;
            if (table[idx].key == key && !table[idx].deleted) {
                table[idx].key = "";
                table[idx].value = -1;
                table[idx].deleted = true;
                return true;
            }
        }
        return false;
    }

    void reset() {
        table.clear();
        table.resize(tablesize);
        collisions = 0;
    }

    int countCollisions() {
        return collisions;
    }
};
