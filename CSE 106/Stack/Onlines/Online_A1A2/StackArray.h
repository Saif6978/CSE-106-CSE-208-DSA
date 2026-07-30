#include <iostream>
using namespace std;

class Stack
{
private:
    int *array;
    //write your code here. Add additional private variables if necessary
    int size;
    int capacity;

public:
    // Constructor
    Stack()
    {
        array = new int[1];
        //write your code here. Initialize additional private variables if necessary junu skibidi
        size=0;
        capacity=1;
    }
    Stack(int initialCapacity)
    {
        array = new int[initialCapacity]; // Allocate initial memory
        capacity=initialCapacity;
        size=0;
        //write your code here. Initialize additional private variables if necessary
    }

    // Destructor
    ~Stack()
    {
        delete[] array; // Free dynamically allocated memory
    }
    // Helper function to resize the array when full
    void resize(int newCapacity)
    {
        if(newCapacity<1){
            newCapacity=1;
        }
        int *newArray = new int[newCapacity]; // Allocate new array
        for(int j=0;j<size;j++){
            *(newArray+j)=*(array+j);
        }
        capacity=newCapacity;
        //write your code here. Copy the elements from the old array to the new array

        delete[] array; // Free old memory
        array=newArray;
        //write your code here. Update the capacity and array pointers
    }

    // Push an element onto the stack
    void push(int x)
    {
        if(size==capacity){
            resize(capacity*2);
        }
        array[size]=x;
        size++;
        //write your code here. Check if the array is full and resize if necessary.
        //push the element onto the stack
    }

    // Remove and return the top element
    int pop()
    {
       if(size==0){
            return -1;
       }
       int x=array[size-1];
       size--;
       if(size<=capacity/4){
            resize(capacity/2);
       }
       return x;
       //write your code here. Check if the stack is empty and return -1 if it is.
       //pop the top element and return it
       //resize the array if necessary
    }

    // Return the top element without removing it
    int top()
    {
        if(size==0){
            return -1;
        }
        return array[size-1];
        //write your code here. Check if the stack is empty and return -1 if it is.
        //return the top element
    }

    // Return the number of elements in the stack
    int length()
    {
        return size;
        //write your code here. Return the number of elements in the stack
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        return (size==0);
        //write your code here. Return true if the stack is empty, false otherwise
    }

    // Clear the stack
    void clear()
    {
        //write your code here. Clear the stack. resize the array to 1
        delete[] array;
        array=new int[1];
        size=0;
        capacity=1;
    }
};
