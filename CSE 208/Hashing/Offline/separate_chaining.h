#include <bits/stdc++.h>
#include "redblack_2205119.h"
using namespace std;

class Hashtable {
public:
    vector<RedBlackTree*> table;
    int tableSize;
    int (*hashfunc)(const string&, int);
    int collisions = 0;

    Hashtable(int size, int (*hf)(const string&, int)) {
        tableSize = size;
        hashfunc = hf;
        collisions = 0;
        table.resize(tableSize);
        for(int i = 0; i < size; i++) {
            table[i] = new RedBlackTree();
        }
    }
    ~Hashtable() {
        for(int i = 0; i < tableSize; i++) {
            delete table[i];
        }
    }
    bool insert(const string& key, int value) {
        int index = hashfunc(key, tableSize);
        Leaf* found = table[index]->find(const_cast<string&>(key), table[index]->source());
        if(found != NIL) {
            return false;
        }
        if (table[index]->nodecount(table[index]->source()) > 0) {
            collisions++;
        }
        table[index]->insert(new Leaf(value, key));
        return true;
    }
    bool search(const string& key, int* probes = nullptr, double* time_ns = nullptr) {
        int idx = hashfunc(key, tableSize);
        if (probes) *probes = 1;
        auto start = chrono::high_resolution_clock::now();
        Leaf* found = table[idx]->find(const_cast<string&>(key), table[idx]->source());
        auto end = chrono::high_resolution_clock::now();
        if (time_ns) {
            *time_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        }
        return (found != NIL);
    }
    bool erase(const string& key) {
        int index = hashfunc(key, tableSize);
        Leaf* found = table[index]->find(const_cast<string&>(key), table[index]->source());
        if(found == NIL) { return false; }
        table[index]->deletion(found);
        return true;
    }
    void reset() {
        for(int i = 0; i < tableSize; i++) {
            table[i]->destroytree(table[i]->source());
            delete table[i];
            table[i] = new RedBlackTree();
        }
        collisions = 0;
    }
    int countCollisions() {
        return collisions;
    }
};
