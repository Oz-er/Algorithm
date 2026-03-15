#include<bits/stdc++.h>
using namespace std;
typedef long long ll;




vector<ll> computelps(string &pattern){
    
    ll patternsize = pattern.size();
    vector<ll>lps(patternsize);

    ll len = 0;
    lps[0] = 0;

    ll i=1;

    while(i<patternsize){
    if(pattern[len]==pattern[i]){
    len++;
    lps[i]=len;
    i++;
    }

    else{
    if(len!=0){
    len = lps[len-1];
    }
    else{
    lps[i]=0;
    i++;
    }
    }
    }


}




int main(){
    string pattern;
    cin>>pattern;

    ll l = pattern.size();

    vector<ll>lps(l);

    lps = computelps(pattern);

}