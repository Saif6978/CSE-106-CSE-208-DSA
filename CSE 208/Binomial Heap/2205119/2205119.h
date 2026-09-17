#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* parent;
    Node* left;
    Node* right;
    int degree;
    Node(){
        data=INT_MIN;
        degree=0;
        parent=left=right=nullptr;
    }
    Node(int val) {
        data = val;
        degree = 0;
        parent = left = right = nullptr;
    }
};
class Bino_Heap {
    map<int, Node*> mp;
    Node* merge_heap(Node* a, Node* b) {
        Node dummy;
        Node* current = &dummy;
        while (a && b) {
            if (a->degree <= b->degree) {
                current->right = a;
                a = a->right;
            } else {
                current->right = b;
                b = b->right;
            }
            current = current->right;
        }
        if (a) current->right = a;
        else current->right = b;
        return dummy.right;
    }

    void link(Node* a, Node* b) {
        a->parent = b;
        a->right = b->left;
        b->left = a;
        b->degree++;
    }
    Node* heap_union(Node* a, Node* b) {
        Node* temp = merge_heap(a, b);
        if (!temp) return nullptr;
        Node* prev = nullptr;
        Node* p = temp;
        Node* next = p->right;
        while (next) {
            if ((p->degree != next->degree) ||
                (next->right && next->right->degree == p->degree)) {
                prev = p;
                p = next;
            } else {
                if (p->data <= next->data) {
                    p->right = next->right;
                    link(next, p);
                } else {
                    if (prev) prev->right = next;
                    else temp = next;
                    link(p, next);
                    p = next;
                }
            }
            next = p->right;
        }
        return temp;
    }
    Node* reverseList(Node* node) {
        Node* prev = nullptr;
        Node* p = node;
        while (p) {
            Node* temp = p->right;
            p->right = prev;
            p->parent = nullptr;
            prev = p;
            p = temp;
        }
        return prev;
    }
    void printBinomialTree(Node* root, int treeNumber) {
        if (!root) return;
        cout << "Binomial Tree, B" << treeNumber << endl;
        queue<pair<Node*, int>> q;
        q.push({root, 0});
        int currentLevel = 0;
        vector<int> levelNodes;
        while (!q.empty()) {
            Node* curr;
            int lvl;
            tie(curr, lvl) = q.front();
            q.pop();
            if (lvl != currentLevel) {
                cout << "Level " << currentLevel << ":";
                for (int key : levelNodes) cout << " " << key;
                cout << endl;
                levelNodes.clear();
                currentLevel = lvl;
            }
            levelNodes.push_back(curr->data);
            Node* child = curr->left;
            vector<Node*> children;
            while (child) {
                children.push_back(child);
                child = child->right;
            }
            for (Node* c : children)
                q.push({c, lvl + 1});
        }
        if (!levelNodes.empty()) {
            cout << "Level " << currentLevel << ":";
            for (int key : levelNodes) cout << " " << key;
            cout << endl;
        }
    }
public:
    Node* root;
    Bino_Heap() {
        root = nullptr;
    }
    Node* Find_Min() {
        if (!root) return nullptr;
        Node* temp = nullptr;
        Node* p = root;
        int m = INT_MAX;
        while (p) {
            if (p->data < m) {
                m = p->data;
                temp = p;
            }
            p = p->right;
        }
        return temp;
    }
    int Extract_Min() {
        if (!root) return -1;
        Node* ans = root;
        Node* temp = nullptr;
        Node* prev = nullptr;
        Node* p = root;
        int min = root->data;
        while (p) {
            if (p->data < min) {
                min = p->data;
                ans = p;
                temp = prev;
            }
            prev = p;
            p = p->right;
        }
        if (temp) temp->right = ans->right;
        else root = ans->right;
        Node* temp2 = reverseList(ans->left);
        Node* child = temp2;
        while (child) {
            child->parent = nullptr;
            mp[child->data] = child;
            child = child->right;
        }
        root = heap_union(root, temp2);
        mp.erase(ans->data);
        delete ans;
        return min;
    }
    void Insert(int key) {
        if (mp.count(key)) return;
        Node* temp = new Node(key);
        Bino_Heap heap;
        heap.root = temp;
        root = heap_union(root, heap.root);
        mp[key] = temp;
    }
    void Update_Key(int old, int key) {
        auto it = mp.find(old);
        if (it == mp.end() || key >= it->second->data) return;
        Node* node = it->second;
        node->data = key;
        mp.erase(old);
        mp[key] = node;
        Node* temp = node;
        Node* prev = temp->parent;
        while (prev && temp->data < prev->data) {
            swap(mp[temp->data], mp[prev->data]);
            swap(temp->data, prev->data);
            temp = prev;
            prev = temp->parent;
        }
    }
    void Remove_Key(int key) {
        auto it = mp.find(key);
        if (it == mp.end()) return;
        Update_Key(key, INT_MIN);
        Extract_Min();
    }
    void Print() {
        cout << "Printing Binomial Heap..." << endl;
        Node* curr = root;
        while (curr) {
            printBinomialTree(curr, curr->degree);
            curr = curr->right;
        }
    }
};
