#include<bits/stdc++.h>
using namespace std;

void Building_table(int n, int r, vector<vector<long long>>& dp){
    for(int i=0;i<=n;i++){
        // j goes up to min(i, r) [cite: 179]
        for(int j=0;j<=min(i, r);j++){
            // Base cases: C(n, n) = 1 or C(n, 0) = 1 [cite: 183-184]
            if(j==0 || j==i){
                dp[i][j] = 1;
            }
            else{
                dp[i][j] = dp[i-1][j-1]+dp[i-1][j];
            }
        }
    }
}

int main(){
    int n, r;
    cin >> n >> r;

    vector<vector<long long>> dp(n+1, vector<long long>(r+1));

    Building_table(n, r, dp);

    cout << "C(" << n << ", " << r << ") = " << dp[n][r] << endl;
}