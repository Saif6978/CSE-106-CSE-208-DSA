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
