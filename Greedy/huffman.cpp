#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// A Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f, Node* l = nullptr, Node* r = nullptr) 
        : ch(c), freq(f), left(l), right(r) {}
};

// Comparator for Priority Queue (Min-Heap)
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq; // Smallest freq at top
    }
};

// Recursive function to print codes
void printCodes(Node* root, string str) {
    if (!root) return;

    // If it's a leaf node (contains a character)
    if (root->ch != '$') {
        cout << root->ch << ": " << str << endl;
    }

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void solveHuffman(vector<char>& data, vector<int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // 1. Create a leaf node for each character and push to heap
    for (size_t i = 0; i < data.size(); ++i) {
        minHeap.push(new Node(data[i], freq[i]));
    }

    // 2. Iterate until heap size is 1
    while (minHeap.size() != 1) {
        // Extract two smallest
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        // Create new internal node with frequency = sum of two
        // '$' is a special marker for internal nodes
        Node* top = new Node('$', left->freq + right->freq, left, right);

        minHeap.push(top);
    }

    // 3. Print the codes
    cout << "Huffman Codes:" << endl;
    printCodes(minHeap.top(), "");
}

int main() {
    vector<char> data = { 'a', 'b', 'c', 'd', 'e', 'f' };
    vector<int> freq = { 5, 9, 12, 13, 16, 45 };

    cout << "--- Huffman Coding ---" << endl;
    solveHuffman(data, freq);

    return 0;
}