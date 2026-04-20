#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

string s1="";
string s2="ATC";



ll dp[1000][1000];

ll LCS(ll a, ll b){

    if(dp[a][b] !=-1){
        return dp[a][b];
    }


    if(a==0 || b==0){
        return 0;
    }

    if(s1[a-1]==s2[b-1]){
        return dp[a][b]=1+LCS(a-1,b-1);
    }

    return dp[a][b]=max(LCS(a,b-1),LCS(a-1,b));

}




string printlcs(ll a,ll b){

    if(a==0 || b==0){
        return "";
    }

    if(s1[a-1] ==s2[b-1]){
        return printlcs(a-1,b-1)+s1[a-1];
    }


    if(dp[a-1][b] > dp[a][b-1]){
        return printlcs(a-1, b);
    }
    else{
        return printlcs(a, b-1);
    }
}



int main(){

    memset(dp,-1,sizeof(dp));

    ll l;

    l=LCS(s1.size(),s2.size());

    cout<<l<<endl;

    for(ll i =0;i<=s1.size();i++){
        for(ll j=0;j<=s2.size();j++){
            cout<<dp[i][j]<<" ";
        }

        cout<<endl;
    }

    string s3;
    s3=printlcs(s1.size(),s2.size());


    cout<<s3<<endl;


    
}