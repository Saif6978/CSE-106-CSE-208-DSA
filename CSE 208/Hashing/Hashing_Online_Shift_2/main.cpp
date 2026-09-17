#include <bits/stdc++.h>
using namespace std;

int hash1(const string& s, int n) {
    unsigned long h = 5381;
    for (char c : s) h = ((h << 5) + h) + (unsigned char)c;
    return (int)(h % n);
}

int hash2(int x, int n) {
    return (x % n + n) % n;
}

struct User {
    string id, permission;
    int state = 0; // 0 empty, 1 occupied, 2 deleted
};

class Inner {
public:
    int n;
    vector<User> t;
    Inner(int x = 0) : n(x), t(x) {}

    bool insert(string id, string p) {
        int h = hash2(stoi(id), n);
        int first_deleted = -1;
        for (int i = 0; i < n; i++) {
            int x = (h + 1LL * i * i) % n;
            if (t[x].state == 1) {
                if (t[x].id == id) {
                    t[x].permission = p;
                    return true;
                }
            } else if (t[x].state == 2) {
                if (first_deleted == -1) first_deleted = x;
            } else { // state == 0 (empty)
                int target = (first_deleted != -1) ? first_deleted : x;
                t[target] = {id, p, 1};
                return true;
            }
        }
        if (first_deleted != -1) {
            t[first_deleted] = {id, p, 1};
            return true;
        }
        return false;
    }

    bool search(string id) {
        int h = hash2(stoi(id), n);
        for (int i = 0; i < n; i++) {
            int x = (h + 1LL * i * i) % n;
            if (t[x].state == 0) return false;
            if (t[x].state == 1 && t[x].id == id) {
                cout << t[x].permission << "\n";
                return true;
            }
        }
        return false;
    }

    bool erase(string id) {
        int h = hash2(stoi(id), n);
        for (int i = 0; i < n; i++) {
            int x = (h + 1LL * i * i) % n;
            if (t[x].state == 0) return false;
            if (t[x].state == 1 && t[x].id == id) {
                cout << "(" << t[x].id << ", " << t[x].permission << ") deleted\n";
                t[x].state = 2;
                return true;
            }
        }
        return false;
    }

    void printAll() {
        bool first = true;
        for (auto &x : t) {
            if (x.state == 1) {
                if (!first) cout << ", ";
                cout << "(" << x.id << ", " << x.permission << ")";
                first = false;
            }
        }
        cout << "\n";
    }
};

struct Group {
    string id;
    Inner inner;
    int state = 0; // 0 empty, 1 occupied, 2 deleted
};

class Outer {
public:
    int n;
    vector<Group> t;
    Outer(int x) : n(x), t(x) {}

    Group* find(string id) {
        int h = hash1(id, n);
        for (int i = 0; i < n; i++) {
            int x = (h + i) % n;
            if (t[x].state == 0) return nullptr;
            if (t[x].state == 1 && t[x].id == id) return &t[x];
        }
        return nullptr;
    }

    Group* get(string id) {
        int h = hash1(id, n);
        int first_deleted = -1;
        for (int i = 0; i < n; i++) {
            int x = (h + i) % n;
            if (t[x].state == 1) {
                if (t[x].id == id) return &t[x];
            } else if (t[x].state == 2) {
                if (first_deleted == -1) first_deleted = x;
            } else { // state == 0
                int target = (first_deleted != -1) ? first_deleted : x;
                t[target].id = id;
                t[target].inner = Inner(n);
                t[target].state = 1;
                return &t[target];
            }
        }
        if (first_deleted != -1) {
            t[first_deleted].id = id;
            t[first_deleted].inner = Inner(n);
            t[first_deleted].state = 1;
            return &t[first_deleted];
        }
        return nullptr;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;
    string line;
    getline(cin, line); // consume remainder of first line

    Outer db(n);
    while (q--) {
        if (!getline(cin, line)) break;
        if (line.empty()) {
            q++; // don't count empty line
            continue;
        }
        stringstream ss(line);
        string op;
        if (!(ss >> op)) {
            q++;
            continue;
        }
        if (op == "INSERT") {
            string g, u, p;
            if (ss >> g >> u >> p) {
                Group* gr = db.get(g);
                if (gr) gr->inner.insert(u, p);
            }
        } else if (op == "SEARCH") {
            string g;
            ss >> g;
            Group* gr = db.find(g);
            string u;
            if (ss >> u) {
                if (!gr) cout << "Group not found\n";
                else if (!gr->inner.search(u))
                    cout << "User not found in group " << g << "\n";
            } else {
                if (!gr) cout << "Group not found\n";
                else gr->inner.printAll();
            }
        } else if (op == "DELETE") {
            string g, u;
            if (ss >> g >> u) {
                Group* gr = db.find(g);
                if (!gr || !gr->inner.erase(u))
                    cout << "User not found in group " << g << "\n";
            }
        }
    }
    return 0;
}
