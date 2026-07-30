#include "bst.h"
#include <iostream>

using namespace std;
int getSecondLargest(Node* node) {
    if (!node || (!node->left && !node->right)) {
        // handle error: tree has < 2 nodes
        return -1; // or throw
    }
    Node* parent = nullptr;
    Node* cur = node;
    // Find the maximum
    while (cur->right) {
        parent = cur;
        cur = cur->right;
    }
    // If maximum has a left subtree, second largest is the rightmost in that subtree
    if (cur->left) {
        cur = cur->left;
        while (cur->right)
            cur = cur->right;
        return cur->val;
    } else {
        // Otherwise, second largest is the parent of the maximum
        return parent->val;
    }
}


int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char option;
    int val;
    int a, b;

    Node *root = NULL;

    while(scanf("%c %d\n", &option, &val) == 2){
        if(option == 'I'){
            root = insertNode(root, val);
            printTree(root);
            printf("\n");
        } else if (option == 'D'){
            root = deleteNode(root, val);
            printTree(root);
            printf("\n");
        } else if (option == 'F'){
            if(find(root, val) != NULL)
                printf("Found\n");
            else
                printf("Not Found\n");
        } else if(option == 'T'){
            if(val == 1){
                inOrder(root);
                printf("\n");
            }
            else if (val == 2)
            {
                preOrder(root);
                printf("\n");
            }
            else{
                postOrder(root);
                printf("\n");
            }
        } else if(option == 'G'){
            root=deleteNode(root,val);
            printf("%d\n", getSecondLargest(root));
        }
    }
    return 0;
}
