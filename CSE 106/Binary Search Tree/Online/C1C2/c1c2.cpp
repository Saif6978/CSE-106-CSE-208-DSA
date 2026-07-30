#include "bst.h"
#include <iostream>

using namespace std;

int countInRange(Node* node, int start, int end) {
    //write your code here
    if (node == nullptr) return 0;

    // If current node's value is less than start, the left subtree is entirely too small
    if (node->val < start) {
        return countInRange(node->right, start, end);
    }
    // If current node's value is greater than end, the right subtree is entirely too large
    if (node->val > end) {
        return countInRange(node->left, start, end);
    }
    // Otherwise, current node is inside the range:
    // count it, plus count from both subtrees (with the same range)
    return 1 + countInRange(node->left, start, end) + countInRange(node->right, start, end);
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
        } else if(option == 'C'){
            a = val;
            scanf("%d\n", &b);
            printf("%d\n", countInRange(root, a, b));
        }
    }
    return 0;
}