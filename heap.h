//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() {
        size = 0;
    }

    void push(int idx, int weightArr[]) {

        // This is the edge case checking whether the heap is full or not
        if (size >= 64) {
            cout << "Overflow: Heap is full." << endl;
            return;
        }


        data[size] = idx;  // Inserts idx as the last item in the heap
        upheap(size, weightArr); // Call upheap() so that it restores the heap order
        size++;  // Increment the size of the heap
    }

    int pop(int weightArr[]) {

        // This is the edge case checking whether the heap is empty
        if (size == 0) {
            cout << "Underflow: Heap is empty." << endl;
            return -1;
        }

        int temp = data[0]; // Stores the root in order to return it
        data[0] = data[size - 1]; // Sets the root to the last heap item
        size--; // Adjusts the size
        downheap(0, weightArr); // Calls downheap() so that it restores heap order
        return temp; // returns the deleted root
    }

    void upheap(int pos, int weightArr[]) {

        int parent = (pos - 1) / 2; // Finds the parent of pos

        // Compares the pos and the parent, swaps if the parent is greater to keep minHeap logic
        while (pos > 0 && weightArr[data[parent]] > weightArr[data[pos]]) {

            // Swap logic
            int temp = data[pos];
            data[pos] = data[parent];
            data[parent] = temp;

            // Percolates up the tree
            pos = parent;
            parent = (pos - 1) / 2;
        }
    }

    void downheap(int pos, int weightArr[]) {

        while (true) {
            // Initializing the children of current node which is pos
            int leftchild = 2 * pos + 1;
            int rightchild = 2 * pos + 2;
            int smallestvalue = pos;

            // Checking to see if the left child exists is smaller than the current smallestvalue
            if (leftchild < size && weightArr[data[leftchild]] < weightArr[data[smallestvalue]]) {
                smallestvalue = leftchild;
            }

            // Checking to see if the right child exists and is smaller than the current smallestvalue
            if (rightchild < size && weightArr[data[rightchild]] < weightArr[data[smallestvalue]]) {
                smallestvalue = rightchild;
            }

            // Checking to see if the parent is already the smallest
            if (smallestvalue == pos) {
                break;
            }

            // Swaps parent with smallest child
            int temp = data[pos];
            data[pos] = data[smallestvalue];
            data[smallestvalue] = temp;

            // Changes pos to be the smallestvalue in order to do the checks again
            pos = smallestvalue;

        }
    }
};

#endif