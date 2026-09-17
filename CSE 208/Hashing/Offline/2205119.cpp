#include<bits/stdc++.h>
#include "double_hashing.h"
#include "separate_chaining.h"
#include "linear_probing.h"
using namespace std;


bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
int nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}


string randomword(mt19937& rng) {
    uniform_int_distribution<int> len_dist(5, 10);
    uniform_int_distribution<int> char_dist(0, 25);
    int len = len_dist(rng);
    string w;
    for (int i = 0; i < len; i++) {
        w += 'a' + char_dist(rng);
    }
    return w;
}
vector<string> generateWords(int n, mt19937& rng) {
    set<string> uniqueWords;
    vector<string> result;
    while ((int)result.size() < n) {
        string w = randomword(rng);
        if (uniqueWords.insert(w).second)
            result.push_back(w);
    }
    return result;
}


int hash_djb2(const string& key, int tableSize) {
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c;
    return hash % tableSize;
}
int hash_djb2_step(const string& key, int tableSize) {
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c;
    int step = (int)((hash % (tableSize - 1)) + 1);
    if (step == 0) step = 1;
    return step;
}
int hash_poly(const string& key, int tableSize) {
    unsigned long long hash = 0, p = 31, p_pow = 1;
    for (char c : key) {
        hash = (hash + (c - 'a' + 1) * p_pow) % tableSize;
        p_pow = (p_pow * p) % tableSize;
    }
    return hash % tableSize;
}
int hash_poly_step(const string& key, int tableSize) {
    unsigned long long hash = 0, p = 37, p_pow = 1;
    for (char c : key) {
        hash = (hash + (c - 'a' + 1) * p_pow) % tableSize;
        p_pow = (p_pow * p) % tableSize;
    }
    int step = (int)((hash % (tableSize - 1)) + 1);
    if (step == 0) step = 1;
    return step;
}

int main() {
    int Nuser;
    cout << "Enter hash table size (N'): ";
    cin >> Nuser;
    int N = nextPrime(Nuser);
    cout << "Using prime table size N = " << N << endl;

    mt19937 rng((unsigned)chrono::system_clock::now().time_since_epoch().count());
    vector<string> words = generateWords(10000, rng);

    vector<double> alphas = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    vector<string> hashNames = {"Hash1 (djb2)", "Hash2 (poly)"};
    vector<int(*)(const string&, int)> hashFuncs = {hash_djb2, hash_poly};

    for (int hfidx = 0; hfidx < (int)hashNames.size(); ++hfidx) {
        string hfName = hashNames[hfidx];
        auto hfunc = hashFuncs[hfidx];

        int (*hash2func)(const string&, int);
        string doubleHLabel;
        if (hfName.find("djb2") != string::npos) {
            hash2func = hash_poly_step;
            doubleHLabel = "DoubleH djb2, poly";
        } else {
            hash2func = hash_djb2_step;
            doubleHLabel = "DoubleH poly, djb2";
        }

        cout << "\n======== " << hfName << " ========\n";
        for (double alpha : alphas) {
            int numToInsert = int(N * alpha);
            if (numToInsert > 10000) numToInsert = 10000;

            Hashtable chainTable(N, hfunc);
            chainTable.reset();
            for (int i = 0; i < numToInsert; i++)
                chainTable.insert(words[i], i + 1);
            int chainCollisions = chainTable.countCollisions();

            double chain_search_time = 0;
            for (int i = 0; i < numToInsert; i++) {
                double t;
                chainTable.search(words[i], nullptr, &t);
                chain_search_time += t;
            }
            chain_search_time /= numToInsert;

            int numToDelete = numToInsert / 10;
            vector<int> toDelete(numToInsert);
            iota(toDelete.begin(), toDelete.end(), 0);
            shuffle(toDelete.begin(), toDelete.end(), rng);
            toDelete.resize(numToDelete);

            set<string> deleted;
            for (int idx : toDelete) {
                chainTable.erase(words[idx]);
                deleted.insert(words[idx]);
            }

            int numQueries = 1000;
            vector<string> queries;
            for (int i = 0; i < numQueries / 2; i++)
                queries.push_back(words[toDelete[i % toDelete.size()]]);
            for (int i = 0, added = 0; added < numQueries / 2 && i < numToInsert; ++i)
                if (!deleted.count(words[i])) {
                    queries.push_back(words[i]);
                    added++;
                }
            double chain_search_time_after = 0;
            for (auto& q : queries) {
                double t;
                chainTable.search(q, nullptr, &t);
                chain_search_time_after += t;
            }
            chain_search_time_after /= numQueries;

            cout << fixed << setprecision(2);
            cout << "[Chaining]           LF=" << alpha
                 << " | Coll: " << chainCollisions
                 << " | t(before): " << chain_search_time << " ns"
                 << " | t(after): " << chain_search_time_after << " ns\n";

            int probeStep = 3;
            Linear lpTable(N, probeStep, hfunc);
            lpTable.reset();
            for (int i = 0; i < numToInsert; i++)
                lpTable.insert(words[i], i + 1);
            int lpCollisions = lpTable.countCollisions();

            double lp_search_time = 0;
            double lp_probe_sum_before = 0;
            for (int i = 0; i < numToInsert; i++) {
                double t; int probes = 0;
                lpTable.search(words[i], &probes, &t);
                lp_search_time += t;
                lp_probe_sum_before += probes;
            }
            lp_search_time /= numToInsert;
            lp_probe_sum_before /= numToInsert;

            deleted.clear();
            for (int idx : toDelete) {
                lpTable.erase(words[idx]);
                deleted.insert(words[idx]);
            }

            double lp_probe_sum_after = 0;
            double lp_search_time_after = 0;
            for (auto& q : queries) {
                double t; int probes = 0;
                lpTable.search(q, &probes, &t);
                lp_search_time_after += t;
                lp_probe_sum_after += probes;
            }
            lp_search_time_after /= numQueries;
            lp_probe_sum_after /= numQueries;

            cout << "[Linear]             LF=" << alpha
                 << " | Coll: " << lpCollisions
                 << " | t(before): " << lp_search_time << " ns"
                 << " | probes(before): " << lp_probe_sum_before
                 << " | t(after): " << lp_search_time_after << " ns"
                 << " | probes(after): " << lp_probe_sum_after << "\n";

            DoubleHashing dhTable(N, hfunc, hash2func);
            dhTable.reset();
            for (int i = 0; i < numToInsert; i++)
                dhTable.insert(words[i], i + 1);
            int dhCollisions = dhTable.countCollisions();

            double dh_search_time = 0;
            double dh_probe_sum_before = 0;
            for (int i = 0; i < numToInsert; i++) {
                double t; int probes = 0;
                dhTable.search(words[i], &probes, &t);
                dh_search_time += t;
                dh_probe_sum_before += probes;
            }
            dh_search_time /= numToInsert;
            dh_probe_sum_before /= numToInsert;

            deleted.clear();
            for (int idx : toDelete) {
                dhTable.erase(words[idx]);
                deleted.insert(words[idx]);
            }

            double dh_probe_sum_after = 0;
            double dh_search_time_after = 0;
            for (auto& q : queries) {
                double t; int probes = 0;
                dhTable.search(q, &probes, &t);
                dh_search_time_after += t;
                dh_probe_sum_after += probes;
            }
            dh_search_time_after /= numQueries;
            dh_probe_sum_after /= numQueries;

            cout << "[" << doubleHLabel << "] LF=" << alpha
                 << " | Coll: " << dhCollisions
                 << " | t(before): " << dh_search_time << " ns"
                 << " | probes(before): " << dh_probe_sum_before
                 << " | t(after): " << dh_search_time_after << " ns"
                 << " | probes(after): " << dh_probe_sum_after << "\n";
        }
    }
    cout << "\nDone!\n";
}
