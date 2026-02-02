#include<bits/stdc++.h>
using namespace std;

void trackback(vector<int>& A, vector<int>& prev, int max_index) {
    vector<int> subarray;
    int curr = max_index;
    
    // Trace back using prev array until we hit a start point (prev=0 logic in slides implies simple connectivity)
    // However, simpler reconstruction is just iterating backwards as long as we are in the interval
    // The slide logic resets prev[i]=0 if A[i] starts new. 
    // We backtrack until prev[curr] == 0 (meaning curr is the start).
    
    while(curr > 0 && prev[curr] != 0) {
        subarray.push_back(A[curr-1]); // A is 0-indexed, indices in DP are 1-based
        curr = prev[curr];
    }
    subarray.push_back(A[curr-1]); // Push the start element

    cout << "Interval: ";
    for (int i = subarray.size() - 1; i >= 0; i--) cout << subarray[i] << " ";
    cout << endl;
}

void Building_table(vector<int>& A, vector<int>& S, vector<int>& prev, int& max_val, int& max_idx) {
    int n = A.size();
    S[0] = 0; // dummy
    
    // DP Logic from Slide 4
    for (int i = 1; i <= n; i++) {
        // Case 1: Extend previous
        S[i] = S[i - 1] + A[i - 1];
        prev[i] = i - 1;

        // Case 2: Start new if current element is better than extending
        if (A[i - 1] > S[i]) {
            S[i] = A[i - 1];
            prev[i] = 0; // 0 indicates start of new interval
        }

        // Track max
        if (S[i] > max_val) {
            max_val = S[i];
            max_idx = i;
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    vector<int> S(n + 1);
    vector<int> prev(n + 1);
    int max_val = -1e9;
    int max_idx = 0;

    Building_table(A, S, prev, max_val, max_idx);

    cout << "Max Sum: " << max_val << endl;
    trackback(A, prev, max_idx);
}