#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vll;
#define f(i,a,b) for(ll i=a;i<b;i++)
#define pb push_back
#define yes cout<<"yes"<<endl
#define no cout<<"no"<<endl


ll rec(vector<vector<ll>>&cost , vector<vector<ll>>&dp, ll x, ll y, ll n, ll m){
  
    if(dp[x][y]!=-1){
        return dp[x][y];
    }

    if(x==n-1 && y==m-1){
        return cost[x][y];
    }
    if(x== n-1){
        return dp[x][y]=cost[x][y]+rec(cost,dp,x,y+1,n,m); 
    }
    else if(y==m-1){
        return dp[x][y]=cost[x][y]+rec(cost,dp,x+1,y,n,m); 
    }

    else return dp[x][y]=cost[x][y]+min(rec(cost,dp,x+1,y,n,m),rec(cost,dp,x,y+1,n,m));



}



void solve(){
   ll n,m,k;
   cin>>n>>m>>k;


   vector<vector<ll>> cost(n, vector<ll>(m));
   vector<vector<ll>>dp(n,vector<ll>(m,-1));
   


   for(ll i=0;i<n;i++){
    for(ll j=0;j<m;j++){
        cost[i][j]=min(i+1,j+1);
    }
   }

   cost[0][0]=0;

   ll total=0;

   ll ans;

   ans=rec(cost,dp,0,0,n,m);

   if(ans==k)yes;
   else no;


}

int main(){
ll t;
cin>>t;
while(t--){
   solve();
}
return 0;
}