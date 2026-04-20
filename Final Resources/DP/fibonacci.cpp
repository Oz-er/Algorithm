#include<bits/stdc++.h>
using namespace std;

void Building_table(int n, vector<long long>& dp){
    // Base cases
    if(n>=0) dp[0] = 0;
    if(n>=1) dp[1] = 1;

    for(int i=2;i<=n;i++){
        dp[i] = dp[i-1]+dp[i-2];
    }
}

int main(){
    int n;
    cin >> n;

    vector<long long> dp(n+1);

    Building_table(n, dp);

    cout << "Fibonacci(" << n << ") = " << dp[n] << endl;
}