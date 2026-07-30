#include <iostream>
#include "QueueLinkedList.h"
using namespace std;

class Stack
{
private:
    Queue que;
    //write your code here. Add additional private variables if necessary

public:
    // Constructor
    /*Stack()
    {

        //write your code here. Initialize additional private variables if necessary
    }
    Stack(int initialCapacity)
    {
        //write your code here. Initialize additional private variables if necessary
    }*/

    // Destructor
    ~Stack()
    {
        que.clear();
    }

    // Push an element onto the stack
    void push(int x)
    {
        Queue temp;
        temp.enqueue(x);
        while(!que.isEmpty()){
            temp.enqueue(que.dequeue());
        }
        while(!temp.isEmpty()){
            que.enqueue(temp.dequeue());
        }
        //write your code here.
        //push the element onto the stack
    }

    // Remove and return the top element
    int pop()
    {
        if(que.isEmpty()){
            return -1;
        }
        return que.dequeue();
       //write your code here. Check if the stack is empty and return -1 if it is.
       //pop the top element and return it
    }

    // Return the top element without removing it
    int top()
    {
        if(que.isEmpty()){
            return -1;
        }
        return que.peek();
        //write your code here. Check if the stack is empty and return -1 if it is.
        //return the top element
    }

    // Return the number of elements in the stack
    int length()
    {
        return que.length();
        //write your code here. Return the number of elements in the stack
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        return que.isEmpty();
        //write your code here. Return true if the stack is empty, false otherwise
    }

    // Clear the stack
    void clear()
    {
        que.clear();
        //write your code here. Clear the stack.

    }
};
