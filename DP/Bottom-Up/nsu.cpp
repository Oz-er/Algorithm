#include<bits/stdc++.h>
using namespace std;

void Building_table(int n, vector<long long>& dp){
    // Base cases [cite: 126-128]
    if(n>=0) dp[0] = 0;
    if(n>=1) dp[1] = 1;
    if(n>=2) dp[2] = 2;

    for(int i=3;i<=n;i++){
        dp[i] = dp[i-1]+dp[i-2]+dp[i-3];
    }
}

int main(){
    int n;
    cin >> n;

    vector<long long> dp(n+1);

    Building_table(n, dp);

    cout << "NSU Number(" << n << ") = " << dp[n] << endl;
}