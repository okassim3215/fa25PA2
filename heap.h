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
        // TODO: insert index at end of heap, restore order using upheap()

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
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()

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
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif