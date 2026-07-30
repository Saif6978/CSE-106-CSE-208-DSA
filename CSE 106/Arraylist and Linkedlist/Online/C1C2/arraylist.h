#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int * array;
    // Add more fields here
    int size;
    int current;
    int capacity;

} ArrayList;


void init_arraylist(ArrayList *list, int capacity)
{
    printf("Memory allocated of capacity %d \n",capacity);
    list->array=(int*)malloc(sizeof(int)*capacity);
    // dynamically allocate space for the array
    list->size=0;
    list->current=-1;
    list->capacity=capacity;
    // initialize the size, capacity, and current position
}


void clear(ArrayList *list)
{
    printf("Array cleared\n");
    list->size=0;
    list->current=-1;
    // clear the list but do not free the array
    // modify the size, capacity, and current position
}

int get_size(ArrayList *list)
{
    printf("Array size is %d\n",list->size);
    return list->size;
}


void resize(ArrayList *list, int new_capacity)
{

    // allocate space for new array with new_capacity
    if(new_capacity<list->capacity){
        printf("Size decreased from %d to %d\n",list->capacity,new_capacity);
        list->array=realloc(list->array,sizeof(int)*new_capacity);
        list->capacity=new_capacity;
    }
    else{
        printf("Size increased from %d to %d\n",list->capacity,new_capacity);
        list->array=realloc(list->array,sizeof(int)*new_capacity);
        list->capacity=new_capacity;
    }
    // print log message

}


void append(ArrayList *list, int value)
{
    printf("Appended %d\n",value);
    // call resize if necessary
    if(list->size>=list->capacity){
        resize(list,2*list->capacity);
    }
    *(list->array+list->size)=value;
    list->size++;

    // add value to the end of the list
}


void insert(ArrayList *list, int value)
{
    printf("Inserted %d\n",value);
    // call resize if necessary
    if(list->size==list->capacity){
        resize(list,2*list->capacity);
    }
    list->size++;
    for(int i=list->size-1;i>list->current+1;i--){
        *(list->array+i)=*(list->array+i-1);
    }
    *(list->array+list->current+1)=value;
    // shift the elements to the right to make space
    // add value at the current position
}


int remove_at_current(ArrayList *list)
{
    int x=*(list->array+list->current+1);
    printf("Removing element %d\n",x);
    for(int i=list->current+2;i<list->size;i++){
        *(list->array+i-1)=*(list->array+i);
    }
    list->size--;
    if(list->size<list->capacity/4){
        resize(list,(list->capacity/2));
    }
    return x;
    // save the value of the current element in a variable
    // shift the elements to the left to fill the gap
    // change the size, and current position as necessary
    // call resize if necessary
    // return the saved value
}

int find(ArrayList *list, int value)
{
    int x=-1;
    for(int i=0;i<list->size;i++){
        if(value== *(list->array+i)){
            x=i;
            break;
        }
    }
    if(x==-1){
        printf("Element not found\n");
    }
    else{
        printf("Found %d in the list at position %d\n",value,x);
    }
    return x;
    // traverse the list and return the position of the value
    // return -1 if the value is not found
}


void move_to_start(ArrayList *list)
{
    if(list->size==0){
        printf("There is no elements\n");
        return;
    }
    printf("Moved to start\n");
    list->current=-1;
    // consider the cases when the list is empty
}


void move_to_end(ArrayList *list)
{
    if(list->size==0){
        printf("There is no elements\n");
        return;
    }
    printf("Moved to end\n");
    list->current=list->size-2;
    // consider the cases when the list is empty
}


void prev(ArrayList *list)
{
    if(list->current!=-1){
        list->current--;
        printf("Moved to previous position %d\n",list->current+1);
    }
    else{
        printf("Current position is already at the start\n");
    }
    // no change if the current position is at the start
}


void next(ArrayList *list)
{
    if(list->current<list->size-2){
        list->current++;
        printf("Moved to next position %d\n",list->current+1);
    }
    else{
        printf("Current position is already at the end\n");
    }
    // no change if the current position is at the end
}


void move_to_position(ArrayList *list, int position)
{
    printf("Moved to position %d\n",position);
    list->current=position-1;

}


int get_current_position(ArrayList *list)
{
    printf("Current position %d\n",list->current+1 );
    return list->current+1;
}


int get_current_element(ArrayList *list)
{
    printf("Current element is %d\n",*(list->array+list->current+1));
    return *(list->array+list->current+1);
}


void print_list(ArrayList *list)
{
    printf("< ");
    for(int i=0;i<list->size;i++){
        if(list->current+1==i){
            printf("|");
        }
        if(i==list->size-1){
            printf("%d",*(list->array+i));
            continue;
        }
        printf("%d  ",*(list->array+i));
    }
    printf(" >\n");
}

void skip(ArrayList *list)
{
    if (list->size == 0) return;
    printf("Skipped\n");
    next(list); // advance cursor
}

void discard(ArrayList *list)
{
    if (list->size == 0) return;
    printf("Discarded\n");
    remove_at_current(list);
    // after removal, the cursor is already on the next element (or at end)
}

void move_and_shift(ArrayList *list, int pos)
{
    if (list->size == 0) {
        printf("List empty, cannot move\n");
        return;
    }

    int cur_idx = list->current + 1;          // index of current element
    int value = list->array[cur_idx];

    printf("Moved to position %d\n", pos);

    // Remove current element
    remove_at_current(list);
    int new_size = list->size;                // size after removal

    // Clamp insertion position
    if (pos < 0) pos = 0;
    if (pos > new_size) pos = new_size;

    // Insert the saved value at position `pos`
    int old_current = list->current;          // save current cursor (not really needed)
    if (pos == 0)
        list->current = -1;
    else
        list->current = pos - 1;
    insert(list, value);

    // Restore cursor so it points to the next book after the original position
    int next_exists = (cur_idx < new_size);   // was there a next element originally?
    if (next_exists) {
        if (pos <= cur_idx) {
            // next element shifted right
            list->current = cur_idx;
        } else {
            // next element stayed at same index
            list->current = cur_idx - 1;
        }
    } else {
        // no next element, cursor at end
        list->current = list->size - 2;
        if (list->current < -1) list->current = -1;
    }
}

void free_list(ArrayList *list)
{
    printf("List freed\n");
    free(list->array);
    list->size=0;
    list->current=-1;
    // free the array before terminating the program
}


