#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;


vector<int> calculate_coins(vector<vector<int>>& dp, vector<int>& coins, int money){
    vector<int> used_coins;
    int n = coins.size();
    int i = n, j = money;

    while(i > 0 && j > 0){
        if(dp[i][j]!=dp[i-1][j]){
            used_coins.push_back(coins[i-1]);
            j-= coins[i-1];
        } else {
            i--;
        }
    }

    return used_coins;
}




void Building_table(vector<int>&coins,vector<vector<int>>&dp,int money){


    int row = dp.size()-1;
    int col = money;

    for (int i=0;i<=row;i++)dp[i][0] = 0;
    for (int j=0;j<=col;j++)dp[0][j] = INF;

    for(int i=1;i<=row;i++){
        for(int j=1;j<=col;j++){
            if(coins[i-1]>j){
                dp[i][j]=dp[i-1][j];
            }
            else{
                dp[i][j]=min(dp[i-1][j],1+dp[i][j-coins[i-1]]);
            }
        }
    }
}



int main(){

    int money;
    cin>>money;

    int n;
    cin>>n;

    vector<int>coins(n);

    
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        coins[i] = a;
    }

    vector<vector<int>>dp(n+1,vector<int>(money+1));
    



    Building_table(coins,dp,money);

    cout<<"max value :"<<dp[n][money]<<endl;


    vector<int>pieces;

    pieces = calculate_coins(dp, coins, money);

    cout << "Coins used: ";
    for(int c : pieces) cout << c << " ";
    cout << endl;
}