//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {

    MinHeap heap;  // Creating new MinHeap object

    // Pushing all the leaf node indices into the heap
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }


    while (heap.size > 1) {

        // Popping the two smallest nodes
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);


        int parent = nextFree; // Creates new node at the index nextFree
        weightArr[parent] = weightArr[left] + weightArr[right]; // Combining the weights and stored into parent
        leftArr[parent] = left; // Left child node for the parent
        rightArr[parent] = right; // Right child node for the parent


        heap.push(parent, weightArr); // Pushes the node back into the heap
        nextFree++; // Incrementing nextFree for next node index
    }
    // Returns the index of the root
    return heap.data[0];

}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {

    stack<pair<int, string>> stack;  // Stack for DFS simulation
    stack.push({root,""}); // Pushing the root into the stack + the empty path


    while (!stack.empty()) {
        auto [node, code] = stack.top(); // Gets the current node and its binary code
        stack.pop();

        // Checks for leaf node
        if (leftArr[node] == -1 && rightArr[node] == -1) {
            int index = charArr[node] - 'a'; // Converts the characters to index
            codes[index] = code; // Stores the code that was generated
        }

        // Checks if there is a left child
        if (leftArr[node] != -1) {
            stack.push({leftArr[node], code + "0"}); // Pushes into stack and appends 0 to it
        }
        // Checks if there is a right child
        if (rightArr[node] != -1) {
            stack.push({rightArr[node], code + "1"}); // Pushes into stack and appends 1 to it
        }
    }


}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}