#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int data;
    // add *next and *prev here
    struct Node* prev;
    struct Node* next;
} Node;


typedef struct
{
    // add Node* head, tail, current_position and other necessary fields here
    Node* head;
    Node* tail;
    Node* current_node;
    int current_position;
    int size;

} LinkedList;


void init_linkedlist(LinkedList *list)
{
    printf("Linked list initialized\n");
    // initialize head, tail with null
    list->head=(Node*)malloc(sizeof(Node));
    list->tail=(Node*)malloc(sizeof(Node));
    list->size=0;
    list->current_position=-1;
    list->head->prev=NULL;
    list->head->next=NULL;
    list->tail->prev=NULL;
    list->tail->next=NULL;
    list->current_node=list->head;
}


void clear(LinkedList *list)
{
    printf("List cleared\n");
    // traverse the list and free each node
    // set head and tail to null
    list->size=0;
    list->current_position=-1;
    list->head->prev=NULL;
    list->head->next=list->tail;
    list->tail->prev=list->head;
    list->tail->next=NULL;
    list->current_node=list->head;

}


int get_size(LinkedList *list)
{
    printf("Size is %d\n",list->size);
    return list->size;
}


void append(LinkedList *list, int value)
{
    printf("Appended %d\n",value);

    if(list->size==0){
        list->head->data=value;
        list->tail->prev=list->head;
        list->head->next=list->tail;
    }
    else if(list->size==1){
        list->tail->data=value;
    }
    else{
        Node* p=(Node*)malloc(sizeof(Node));
        p->data=value;
        list->tail->next=p;
        p->prev=list->tail;
        list->tail=p;
        list->tail->next=NULL;

    }
    list->size++;
    // create a new node and set its value
    // consider the case when the list is empty and when it isnt
}


void insert(LinkedList *list, int value)
{
    printf("Inserted %d \n",value);
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=value;
    if(list->current_position+1==0){
        temp->next=list->head;
        temp->prev=NULL;
        list->head->prev=temp;
        list->head=temp;
    }
    else if(list->current_position+2==list->size){
        list->tail->next=temp;
        temp->prev=list->tail;
        temp->next=NULL;
        list->tail=temp;
    }
    else{
        temp->next=list->current_node;
        temp->prev=list->current_node->prev;
        list->current_node->prev=temp;
        list->current_node=temp;
    }
    list->size++;
    // create a new node and set its value
    // place it at the current position (check order of operations)
    // consider the case when the list is empty and when it isnt
}


int remove_at_current(LinkedList *list)
{

    int x;
    if(list->current_position+1==0){
        x=list->head->data;
        list->head=list->head->next;
        list->head->prev=NULL;
    }
    else if(list->current_position+2==list->size){
        x=list->tail->data;
        list->tail=list->tail->prev;
        list->tail->next=NULL;
    }
    else{
        x=list->current_node->data;
        list->current_node->prev->next=list->current_node->next;
        list->current_node->next->prev=list->current_node->prev;
        list->current_node=list->current_node->next;
    }
    list->size--;
    printf("Removed %d\n",x);
    // consider the case when current code is at the begining or at the end
    return x;
}


int find(LinkedList *list, int value)
{
    // traverse the list and return the position of the value
    Node* temp=list->head;
    int count=0;
    while(temp!=NULL){
        count++;
        if(temp->data==value){
            printf("%d found at position %d\n",value,count);
            return count;
        }
        temp=temp->next;
    }
    printf("%d not found\n",value);
    return -1;
}


void move_to_start(LinkedList *list)
{
    if(list->size==0){
        printf("There is no elements\n");
        return;
    }
    printf("Moved to start\n");
    list->current_node=list->head;
    list->current_position=-1;
}


void move_to_end(LinkedList *list)
{
    if(list->size==0){
        printf("There is no elements\n");
        return;
    }
    printf("Moved to end\n");
    list->current_node=list->tail;
    list->current_position=list->size-2;
}


void prev(LinkedList *list)
{
    if(list->current_position!=-1){
        list->current_position--;
        list->current_node=list->current_node->prev;
        printf("Moved to previous position %d\n",list->current_position+1);
        return;
    }
    printf("Current position is already at the start\n");
}


void next(LinkedList *list)
{

    if(list->current_position<list->size-2){
            printf("Moved to next position %d\n",list->current_position+2);
        list->current_position++;
        list->current_node=list->current_node->next;
        return;
    }
    printf("Current position is already at the end\n");
}


void move_to_position(LinkedList *list, int position)
{
    printf("Moved from %d to %d\n",list->current_position,position);
    if(position>list->current_position){
        while(list->current_position+1<position){
            list->current_position++;
            list->current_node=list->current_node->next;
        }
    }
    else{
        while(list->current_position>position){
            list->current_position--;
            list->current_node=list->current_node->prev;
        }
    }
    // traverse the list and stop at the given position
}


int get_current_position(LinkedList *list)
{
    printf("Current position is %d\n",list->current_position+1);
    // traverse the list and stop when you are at the current position
    // return the position (integer)

    return list->current_position+1;
}


int get_current_element(LinkedList *list)
{
    printf("Current element is %d\n",list->current_node->data);
    // return the value at the current position
    return list->current_node->data;
}


void print_list(LinkedList *list)
{
    printf("< ");
    Node* temp=list->head;

    for(int i=0;i<list->size;i++){
        if(i==list->current_position+1){
            printf("|");
        }
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf(">\n");
}

void skip(LinkedList *list)
{
    if (list->size == 0) return;
    printf("Skipped\n");
    if (list->current_position + 1 < list->size - 1) {
        list->current_node = list->current_node->next;
        list->current_position++;
    } else {
        printf("Already at end\n");
    }
}

void discard(LinkedList *list)
{
    if (list->size == 0) return;
    printf("Discarded\n");

    Node *to_remove = list->current_node;
    Node *prev = to_remove->prev;
    Node *next = to_remove->next;

    // Unlink the node
    if (prev) prev->next = next;
    else list->head = next;
    if (next) next->prev = prev;
    else list->tail = prev;

    free(to_remove);
    list->size--;

    // Move cursor to the next node, or to the previous one if none
    if (next) {
        list->current_node = next;
        // current_position unchanged
    } else {
        list->current_node = prev;
        list->current_position = list->size - 2;
        if (list->current_position < -1) list->current_position = -1;
    }
}

void move_and_shift(LinkedList *list, int pos)
{
    if (list->size == 0) {
        printf("List empty, cannot move\n");
        return;
    }

    printf("Moved to position %d\n", pos);

    Node *cur_node = list->current_node;
    int cur_idx = list->current_position + 1;
    int value = cur_node->data;
    Node *prev = cur_node->prev;
    Node *next = cur_node->next;   // next book after current (may be NULL)

    // Remove current node
    if (prev) prev->next = next;
    else list->head = next;
    if (next) next->prev = prev;
    else list->tail = prev;

    list->size--;

    // Clamp insertion position
    if (pos < 0) pos = 0;
    if (pos > list->size) pos = list->size;

    // Find node before which to insert
    Node *insert_before;
    if (pos == list->size) {
        insert_before = NULL;   // append
    } else {
        insert_before = list->head;
        for (int i = 0; i < pos; i++)
            insert_before = insert_before->next;
    }

    // Insert cur_node at the target position
    if (insert_before == NULL) { // append
        cur_node->prev = list->tail;
        cur_node->next = NULL;
        if (list->tail) list->tail->next = cur_node;
        else list->head = cur_node;
        list->tail = cur_node;
    } else {
        cur_node->prev = insert_before->prev;
        cur_node->next = insert_before;
        if (insert_before->prev) insert_before->prev->next = cur_node;
        else list->head = cur_node;
        insert_before->prev = cur_node;
    }
    list->size++;

    // Set cursor to the node that now occupies the original position (next book)
    if (next != NULL) {
        // Find node at index cur_idx in the new list
        Node *new_current = list->head;
        for (int i = 0; i < cur_idx && i < list->size; i++)
            new_current = new_current->next;
        list->current_node = new_current;
        list->current_position = cur_idx - 1;
        if (list->current_position < -1) list->current_position = -1;
    } else {
        // No next book – cursor at end
        list->current_node = list->tail;
        list->current_position = list->size - 2;
        if (list->current_position < -1) list->current_position = -1;
    }
}

void free_list(LinkedList *list)
{
    printf("List freed\n");
    // free each node in the list
    while(list->head!=NULL){
        Node* temp=list->head->next;
        free(list->head);
        list->head=temp;
        temp=NULL;
    }
}
