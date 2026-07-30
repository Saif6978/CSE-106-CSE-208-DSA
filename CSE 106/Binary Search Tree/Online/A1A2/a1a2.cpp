#include "bst.h"
#include <iostream>

using namespace std;

Node*  lca(Node* node, int a, int b){
    // Write your code here.
    // If both values are smaller, go left
    if (a < node->val && b < node->val)
        return lca(node->left, a, b);
    // If both are larger, go right
    else if (a > node->val && b > node->val)
        return lca(node->right, a, b);
    // Otherwise, current node is the LCA
    else
        return node;
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
        } else if(option == 'L'){
            a = val;
            scanf("%d\n", &b);
            printf("%d\n", lca(root, a, b)->val);
        }
    }
    return 0;
}