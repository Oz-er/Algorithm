#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


vector<int> val = {1,2,3};
vector<int> wt = {4,5,1};

int dp[100][100];

int knapsack(int ind, int wt_left){

    if(wt_left == 0) return 0;
    if(ind<0) return 0;


    if(dp[ind][wt_left] != -1) return dp[ind][wt_left];
    
    
    //1.dont choose
    int ans = knapsack(ind-1,wt_left);
    
    
    
    //2.choose
    if(wt_left - wt[ind] >=0){
    ans = knapsack(ind-1,wt_left-wt[ind]) + val[ind];
    }


    return dp[ind][wt_left]=ans;
}

int main(){

    memset(dp,-1,sizeof(dp));

    int w = 4;

    cout<<knapsack(val.size()-1,w)<<endl;
}