#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vll;
#define f(i,a,b) for(ll i=a;i<b;i++)
#define pb push_back
#define yes cout<<"yes"<<endl
#define no cout<<"no"<<endl

// vll v={1,3,6,10,15};

//memoize the changing variable

ll dp[10010];

ll cc(ll amount,vector<ll>&v){

    if(amount==0)return 0;
    if(dp[amount]!=-1)return dp[amount];

    ll ans= LONG_LONG_MAX;

    for(ll coin : v){
        if(amount-coin >=0){
            ans = min(ans, cc(amount-coin,v)+1);          
        }
    }

    return dp[amount]=ans;
}


void solve(ll amount,vector<ll>&v){

    memset(dp,-1,sizeof(dp));

    ll ans = cc(amount,v);

    if(ans==LONG_LONG_MAX){
        cout<<-1<<endl;
    }
    else{
        cout<<ans<<endl;
    }
}

int main(){
ll t;
cin>>t;
while(t--){
    solve();
}
return 0;
}