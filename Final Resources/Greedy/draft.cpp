#include<bits/stdc++.h>
using namespace std;


struct Node{
    char ch;
    int freq;
    Node *left,*right;

    Node(char c,int f, Node* l=nullptr, Node* r=nullptr){
        ch=c;
        freq=f;
        left=l;
        right=r;
    }
};


struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq; // Smallest freq at top
    }
};


void generateCodes(Node* root, string str, map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}



void huffman_generator(vector<char>&data, vector<int> &freq,map<char, string>& codeMap){

    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for(int i=0;i<data.size();i++){
        minHeap.push(new Node(data[i],freq[i]));
    }


    while(minHeap.size()!=1){

        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* top = new Node('#',left->freq + right->freq, left, right);
        minHeap.push(top);
    }

    generateCodes(minHeap.top(), "", codeMap);
}




int main(){

    string text;
    cin>>text;

    if(text.empty())return 0;

    map<char, int> freqMap;
    for(char ch : text){
        freqMap[ch]++;
    }


    vector<char> data;
    vector<int> freq;
    for(auto pair : freqMap){
        data.push_back(pair.first);
        freq.push_back(pair.second);
    }


    map<char, string> huffmanCode;
    huffman_generator(data, freq, huffmanCode);
    

    for(auto pair : huffmanCode){
        cout<<(int)pair.first<<" "<<pair.second<<endl;
    }

}






// bool compare(Node* l,Node* r){
//     return l->freq>r->freq;
// }



//default behaviour of priority queue(max heap)
// priority_queue<int> pq;
// pq.push(10);
// pq.push(5);
// pq.push(20);
// pq.top(); // 20

