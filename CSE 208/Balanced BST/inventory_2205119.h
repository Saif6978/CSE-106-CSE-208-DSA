#include <iostream>
#include "redblack_2205119.h"
using namespace std;

class Inventory {
    RedBlackTree tree;
public:
    Inventory() = default;
    ~Inventory() = default;

    void Additem(int id, string& name, int stock, ostream& out) {
        Leaf* existing = tree.find(id, tree.source());
        if (existing != NIL) {
            existing->stock = stock;
            existing->name = name;
            tree.printTreeFormat(tree.source(), out, false);
            tree.printTreeFormat(tree.source(), cout, true);
            out << endl;
            cout << endl;
            return;
        }
        Leaf* node = new Leaf(id, name, stock);
        tree.insert(node);
        tree.printTreeFormat(tree.source(), out, false);
        tree.printTreeFormat(tree.source(), cout, true);
        out << endl;
        cout << endl;
    }

    void Buyitem(int id, int stock, ostream& out) {
        Leaf* leaf = tree.find(id, tree.source());
        if (leaf == NIL) {
            out << "Not found" << endl;
            cout << "Not found" << endl;
            return;
        }
        if (leaf->stock <= stock) {
            tree.deletion(leaf);
            tree.printTreeFormat(tree.source(), out, false);
            tree.printTreeFormat(tree.source(), cout, true);
            out << endl;
            cout << endl;
            return;
        }
        leaf->stock -= stock;
        tree.printTreeFormat(tree.source(), out, false);
        tree.printTreeFormat(tree.source(), cout, true);
        out << endl;
        cout << endl;
    }

    void Checkitem(int id, ostream& out) {
        Leaf* leaf = tree.find(id, tree.source());
        if (leaf != NIL) {
            out << "Stock left: " << leaf->stock << endl;
            cout << "Stock left: " << leaf->stock << endl;
        } else {
            out << "Not available" << endl;
            cout << "Not available" << endl;
        }
    }

    void Clearinventory(ostream& out) {
        if (tree.source() == NIL) {
            out << "unsuccessful" << endl;
            cout << "unsuccessful" << endl;
            return;
        }
        tree.clear();
        out << "successful" << endl;
        cout << "successful" << endl;
    }

    int Inventorysize() {
        return tree.nodecount(tree.source());
    }

    bool is_empty() {
        return tree.nodecount(tree.source()) == 0;
    }

    void ListInventory(ostream& out) {
        tree.inorder(tree.source(), out);
    }
};
