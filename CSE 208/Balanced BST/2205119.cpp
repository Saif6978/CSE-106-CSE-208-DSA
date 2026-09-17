#include <iostream>
#include <fstream>
#include <string>
#include "inventory_2205119.h"
using namespace std;

int main() {
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Error opening file.\n";
        return 1;
    }

    Inventory inv;

    string s;
    while (infile >> s) {
        if (s == "AI") {
            int id, stock;
            string name;

            infile >> id;

            infile >> ws;
            char ch = infile.peek();

            if (ch == '\"') {
                infile.get();
                getline(infile, name, '\"');
                infile >> stock;
            } else {
                infile >> name >> stock;
            }

            inv.Additem(id, name, stock, outfile);
        }
        else if (s == "BI") {
            int pid, st;
            infile >> pid >> st;
            inv.Buyitem(pid, st, outfile);
        }
        else if (s == "CI") {
            int cid;
            infile >> cid;
            inv.Checkitem(cid, outfile);
        }
        else if (s == "Clr") {
            inv.Clearinventory(outfile);
        }
        else if (s == "S") {
            int sz = inv.Inventorysize();
            cout << sz << "\n";
            outfile << sz << "\n";
        }
        else if (s == "Em") {
            string output = inv.is_empty() ? "yes\n" : "no\n";
            cout << output;
            outfile << output;
        }
        else if (s == "Itr") {
            inv.ListInventory(outfile);
        }
        else {
            break;
        }
    }
    infile.close();
    outfile.close();
    return 0;
}
