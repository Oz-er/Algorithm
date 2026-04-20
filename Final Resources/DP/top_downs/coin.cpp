#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[10005];
const ll INF=1e18;

ll coincalc(vector<ll>&coins, ll w){

    if(w==0)return 0;
    if(w<0)return 1e18;

    if(dp[w]!=-1)return dp[w];

    ll ans =INF;

    for(ll coin : coins){
        ans = min(ans,1+coincalc(coins,w-coins[coin]));
    }


    return dp[w]=ans;
}







int main(){

    memset(dp,-1,sizeof(dp));

    vector<ll>coins ={1,5,6,9};
    ll money = 10;

    ll ans = coincalc(coins,money);

}