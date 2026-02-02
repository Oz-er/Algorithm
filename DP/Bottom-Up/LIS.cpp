#include<bits/stdc++.h>
using namespace std;


vector<int> trackback(vector<int>& arr, vector<int>& prev, int max_index){
    vector<int> lis;
    int curr = max_index;
    
    while(curr != -1){
        lis.push_back(arr[curr]);
        curr = prev[curr];
    }
    reverse(lis.begin(), lis.end());
    return lis;
}


void Building_table(vector<int>& arr, vector<int>& dp, vector<int>& prev, int& max_len, int& max_idx){
    int n = arr.size();
    
    for(int i=0;i<n;i++){
        dp[i] = 1;
        prev[i] = -1;
        
        for(int j=0;j<i;j++){
            if(arr[j] < arr[i] && dp[j] + 1 > dp[i]){
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }

        if(dp[i] > max_len){
            max_len = dp[i];
            max_idx = i;
        }
    }
}


int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin >> arr[i];

    vector<int> dp(n);
    vector<int> prev(n);
    int max_len = 0;
    int max_idx = 0;

    Building_table(arr, dp, prev, max_len, max_idx);

    cout << "LIS Length: " << max_len << endl;

    vector<int> result = trackback(arr, prev, max_idx);
    cout << "LIS Sequence: ";
    for(int x : result) cout << x << " ";
    cout << endl;
}