#include <iostream>
using namespace std;

class Queue
{
private:
    int *array;
    //write your code here. Add additional private variables if necessary
    int capacity;
    int size;

public:
    // Constructor
    Queue()
    {
        array = new int[1];
        capacity=1;
        size=0;
        //write your code here. Initialize additional private variables if necessary
    }
    Queue(int initialCapacity)
    {
        array = new int[initialCapacity]; // Allocate initial memory
        capacity=initialCapacity;
        size=0;
        //write your code here. Initialize additional private variables if necessary
    }

    // Destructor
    ~Queue()
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
        for(int i=0;i<size;i++){
            newArray[i]=array[i];
        }
        capacity=newCapacity;
        //write your code here. Copy the elements from the old array to the new array

        delete[] array; // Free old memory
        array=newArray;
        //write your code here. Update the capacity and array pointers
    }

    // Enqueue an element onto the queue
    void enqueue(int x)
    {
        if(size==capacity){
            resize(2*capacity);
        }
        array[size]=x;
        size++;
        //write your code here. Check if the array is full and resize if necessary.
    }

    // Remove and return the peek element
    int dequeue()
    {
        if(size==0){
            return -1;
        }
        int x=array[0];
        for(int i=1;i<size;i++){
            array[i-1]=array[i];
        }
        size--;
        if(size<=capacity/4){
            resize(capacity/2);
        }
        return x;
       //write your code here. Check if the stack is empty and return -1 if it is.
       //remove the peek element and return it
       //resize the array if necessary
    }

    // Return the peek element without removing it
    int peek()
    {
        if(size==0){
            return -1;
        }
        return array[0];
        //write your code here. Check if the queue is empty and return -1 if it is.
        //return the peek element
    }

    // Return the number of elements in the queue
    int length()
    {
        return size;
        //write your code here. Return the number of elements in the queue
    }

    // Check if the queue is empty
    bool isEmpty()
    {
        return (size==0);
        //write your code here. Return true if the queue is empty, false otherwise
    }

    // Clear the queue
    void clear()
    {
        delete[] array;
        array= new int[1];
        capacity=1;
        size=0;
        //write your code here. Clear the queue. resize the array to 1
    }
};
