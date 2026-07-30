#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <fstream>
#include <climits> 
#include <stdexcept>

#define MAX_CAPACITY 100  //Defines the maximum capacity of the heap

class MaxHeap
{
private:
    int heap[MAX_CAPACITY];  //Array to store heap elements
    int size;                //Current number of elements in the heap

    //Sifts up the node at index i to maintain heap property
    void siftUp(int i)
    {
        /**Write your code here**/
        while(i>0 && heap[i]>heap[(i-1)/2]){//i==0 mane top e ase so out // heap condition check
            int temp=heap[(i-1)/2];
            heap[(i-1)/2]=heap[i];
            heap[i]=temp;
            i=(i-1)/2;
        }
    }

    //Sifts down the node at index i to maintain heap property
    void siftDown(int i)
    {
        while(2*i+1<size){//mane child exist kortese
            int m=i;//parent
            int l=2*i+1;//left
            int r=2*i+2;//right
            if(l<size && heap[l]>heap[m]){
                m=l;
            }
            if(r<size && heap[r]>heap[m]){
                m=r;
            }
            if(m==i){
                break;
            }
            int temp=heap[i];
            heap[i]=heap[m];
            heap[m]=temp;
            i=m;
        }
        /**Write your code here**/
    }

public:
    //Constructor initializes an empty heap
    MaxHeap() : size(0) {}

    //Inserts a new element x into the heap
    void insert(int x)
    {
        if (size == MAX_CAPACITY)
        {
            throw std::length_error("insert() called, but the heap is full.");
        }
        heap[size]=x;
        siftUp(size);
        size++;
        /**Write your code here**/

    }

    //Returns the maximum element without removing it
    int findMax()
    {
        if (size == 0)
        {
            throw std::runtime_error("findMax() called, but the heap is empty.");
        }
        return heap[0];
        /**Write your code here**/

    }

    //Removes and returns the maximum element from the heap
    int extractMax()
    {
        if (size == 0)
        {
            throw std::runtime_error("extractMax() called, but the heap is empty.");
        }
        int r=heap[0];
        heap[0]=heap[size-1];
        size--;
        siftDown(0);
        return r;
        /**Write your code here**/

    }


    //Returns the number of elements in the heap
    int getSize()
    {
        /**Write your code here**/
        return size;
    }

    //Checks if the heap is empty. Returns true if the heap is empty, false otherwise.
    bool isEmpty()
    {
        /**Write your code here**/
        return (size==0);
    }

    //Increases the value of the element at index i to new_value
    void increaseKey(int i, int newValue)
    {
        if (i < 0 || i >= size || heap[i] >= newValue)
        {
            throw std::invalid_argument("increaseKey() called with invalid index or invalid new value.");
        }
        heap[i]=newValue;
        siftUp(i);
        /**Write your code here**/

    }


    //Deletes the element at index i
    void deleteKey(int i)
    {
        increaseKey(i,INT_MAX);
        extractMax();
        /**Write your code here**/
    }

    //Prints the heap's content to the output file
    void printHeap(std::ofstream &outfile)
    {
        for(int i=0;i<size;i++){
            outfile<< heap[i] << " ";
        }
        outfile << std::endl;
        /**Write your code here**/
    }

    //Checkes whether the Max Heap property is preserved or not. Returns true if the Max Heap property is valid and returns false otherwise.
    bool isValidMaxHeap() {
        for (int i = 0; i < size / 2; ++i) {
            if (heap[i] < heap[2*i+1] || (2*i+2 < size && heap[i] < heap[2*i+2]))
                return false;
        }
        return true;
    }
};

#endif //MAXHEAP_H
