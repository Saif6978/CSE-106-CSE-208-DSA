#include<bits/stdc++.h>
#include "color.hpp"
using namespace std;
const int RED=1;
const int BLACK =0;
#define red dye::red

class Leaf {
public:
    int num;
    int color=BLACK;
    string name;
    int stock;
    Leaf* left;
    Leaf* right;
    Leaf* parent;
    Leaf() {
        num=-1;
        color=BLACK;
        name="";
        stock=-1;
        left=nullptr;
        right=nullptr;
        parent=nullptr;
    }
    Leaf(int num , string name , int stock) {
        this->num = num;
        this->color = RED;
        this->name=name;
        this->stock=stock;
        left=nullptr;
        right=nullptr;
        parent=nullptr;
    }
};

Leaf* NIL=nullptr;

inline void init_NIL() {
    NIL=new Leaf();
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
}

class RedBlackTree {
    Leaf* root;

    Leaf* bst_insert(Leaf* root, Leaf* node) {
        if (root == NIL) {
            return node;
        }
        if (node->num < root->num) {
            Leaf* leftChild = bst_insert(root->left, node);
            root->left = leftChild;
            leftChild->parent = root;
        } else if (node->num > root->num) {
            Leaf* rightChild = bst_insert(root->right, node);
            root->right = rightChild;
            rightChild->parent = root;
        } else {

        }

        return root;
    }

    void transplant(Leaf* prev, Leaf* next) {
        if (prev->parent == NIL) {
            root = next;
        }
        else if (prev == prev->parent->left) {
            prev->parent->left = next;
        }
        else {
            prev->parent->right = next;
        }
        next->parent = prev->parent;
    }

    Leaf* minimum(Leaf* node) {
        while (node->left != NIL) {
            node=node->left;
        }
        return node;
    }

    Leaf* successor(Leaf* root) {
        root=root->right;
        while (root!=NIL && root->left!=NIL) {
            root=root->left;
        }
        return root;
    }
    Leaf* predecessor(Leaf* root){
        root=root->left;
        while(root!=NIL && root->right!=NIL){
            root=root->right;
        }
        return root;
    }
    void fixinsert(Leaf* node) {
        while (node->parent!=NIL && node->parent->color==RED) {
            if (node->parent==node->parent->parent->left) {
                Leaf* uncle=node->parent->parent->right;
                if (uncle && uncle->color==RED) {
                    node->parent->color=BLACK;
                    uncle->color=BLACK;
                    node->parent->parent->color=RED;
                    node=node->parent->parent;
                }
                else {
                    if (node==node->parent->right) {
                        node=node->parent;
                        left_rotate(node);
                    }
                    node->parent->color=BLACK;
                    node->parent->parent->color=RED;
                    right_rotate(node->parent->parent);
                }
            }
            else {
                Leaf* uncle=node->parent->parent->left;
                if (uncle && uncle->color==RED) {
                    node->parent->color=BLACK;
                    uncle->color=BLACK;
                    node->parent->parent->color=RED;
                    node=node->parent->parent;
                }
                else {
                    if (node==node->parent->left) {
                        node=node->parent;
                        right_rotate(node);
                    }
                    node->parent->color=BLACK;
                    node->parent->parent->color=RED;
                    left_rotate(node->parent->parent);
                }
            }
        }
        root->color=BLACK;
    }

    void left_rotate(Leaf* node) {
        Leaf* temp = node->right;
        node->right=temp->left;
        if (temp->left!=NIL) {
            temp->left->parent=node;
        }
        temp->parent=node->parent;
        if (node->parent==NIL) {
            root=temp;
        }
        else if (node->parent->left==node) {
            node->parent->left=temp;
        }
        else {
            node->parent->right=temp;
        }
        temp->left=node;
        node->parent=temp;
    }

    void right_rotate(Leaf* node) {
        Leaf* temp = node->left;
        node->left=temp->right;
        if (temp->right!=NIL) {
            temp->right->parent=node;
        }
        temp->parent=node->parent;
        if (node->parent==NIL) {
            root=temp;
        }
        else if (node->parent->right==node) {
            node->parent->right=temp;
        }
        else {
            node->parent->left=temp;
        }
        temp->right=node;
        node->parent=temp;
    }

    void fixdel(Leaf* node) {
        while (node != root && node->color==BLACK) {
            if (node==node->parent->left) {
                Leaf* uncle = node->parent->right;
                if (uncle!=NIL && uncle->color==RED) {
                    uncle->color=BLACK;
                    node->parent->color=RED;
                    left_rotate(node->parent);
                    uncle=node->parent->right;
                }
                if (uncle!=NIL &&(uncle->left==NIL || uncle->left->color==BLACK)
                    &&(uncle->right==NIL || uncle->right->color==BLACK)) {
                    uncle->color=RED;
                    node=node->parent;
                }
                else {
                    if (uncle!=NIL && (uncle->right==NIL || uncle->right->color==BLACK)) {
                        if (uncle->left!=NIL)uncle->left->color=BLACK;
                        uncle->color=RED;
                        right_rotate(uncle);
                        uncle=node->parent->right;
                    }
                    if (uncle!=NIL)uncle->color=node->parent->color;
                    node->parent->color=BLACK;
                    if (uncle->right!=NIL)uncle->right->color=BLACK;
                    left_rotate(node->parent);
                    node=root;
                }
            }
            else {
                Leaf* uncle = node->parent->left;
                if (uncle!=NIL && uncle->color==RED) {
                    uncle->color=BLACK;
                    node->parent->color=RED;
                    right_rotate(node->parent);
                    uncle=node->parent->left;
                }
                if (uncle != NIL && (uncle->right == NIL || uncle->right->color == BLACK)
                    && (uncle->left == NIL || uncle->left->color == BLACK)) {
                    uncle->color=RED;
                    node=node->parent;
                }
                else {
                    if (uncle!=NIL &&(uncle->left ==NIL || uncle->left->color==BLACK)) {
                        if (uncle->right!=NIL)uncle->right->color=BLACK;
                        uncle->color=RED;
                        left_rotate(uncle);
                        uncle=node->parent->left;
                    }
                    uncle->color=node->parent->color;
                    node->parent->color=BLACK;
                    if (uncle->left!=NIL)uncle->left->color=BLACK;
                    right_rotate(node->parent);
                    node=root;
                }
            }
        }
        node->color=BLACK;
    }

    public:

    RedBlackTree() {
        if (NIL==nullptr)init_NIL();
        root = NIL;
    }

    ~RedBlackTree() {
        destroytree(root);
    }

    Leaf* source() {
        return root;
    }

    void insert(Leaf* node) {
        node->left=NIL;
        node->right=NIL;
        node->parent=NIL;
        root=bst_insert(root,node);
        fixinsert(node);
    }

    Leaf* find(int num,Leaf* root ) {
        if (root == NIL) {
            return NIL;
        }
        if (root->num==num) {
            return root;
        }
        if (root->num>num) {
            return find(num,root->left);
        }
        return find(num,root->right);
    }

    void inorder(Leaf* root,ostream& out) {
        if (root != NIL) {
            inorder(root->left,out);
            out << root->num << " => " << root->name << " (" << root->stock << ") " << endl;
            cout << root->num << " => " << root->name << " (" << root->stock << ") " << endl;
            inorder(root->right,out);
        }
    }

    void deletion(Leaf* node) {
        Leaf* temp=node;
        Leaf* x;
        int temp_Og=temp->color;
        if (node->left ==NIL) {
            x=node->right;
            transplant(node,node->right);

        }
        else if (node->right == NIL) {
            x=node->left;
            transplant(node,node->left);
        }
        else {
            temp=minimum(node->right);
            temp_Og=temp->color;
            x=temp->right;
            if (temp->parent==node) {
                x->parent=temp;
            }
            else {
                transplant(temp,temp->right);
                temp->right=node->right;
                temp->right->parent=temp;
            }
            transplant(node,temp);
            temp->left=node->left;
            temp->left->parent=temp;
            temp->color=node->color;
        }
        delete node;
        if (temp_Og==BLACK) {
            fixdel(x);
        }
    }

    void clear() {
        destroytree(root);
        root = NIL;
    }

    void destroytree(Leaf* node) {
        if (node!=NIL && node!=nullptr) {
            destroytree(node->left);
            destroytree(node->right);
            delete node;
        }
    }

    int nodecount(Leaf* node) {
        if (node==NIL || node==nullptr) return 0;
        return 1+nodecount(node->left)+nodecount(node->right);
    }

    void printTreeFormat(Leaf* node,ostream& out, bool colorize = false) {
        if (node == NIL || node == nullptr) return;
        if (node->color==RED && colorize) {
            out << node->num << "_" << red(node->name);
        }
        else {
            out << node->num << "_" << node->name;
        }
        if (node->left != NIL || node->right != NIL) {
            out << "(";
            if (node->left != NIL)
                printTreeFormat(node->left,out,colorize);
            out << ",";
            if (node->right != NIL)
                printTreeFormat(node->right,out,colorize);
            out << ")";
        }
    }
};
