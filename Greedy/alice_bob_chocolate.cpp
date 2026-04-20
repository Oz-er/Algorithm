#include<bits/stdc++.h>
using namespace std;

typedef long long ll;


void solve(){

    ll chocolates;
    vector<ll>alice_time;
    vector<ll>bob_time;
    cin>>chocolates;

    for(ll i=0;i<chocolates;i++){
    ll a;
    cin>>a;
    alice_time.push_back(a);
    bob_time.push_back(a);
    }



    reverse(bob_time.begin(),bob_time.end());


    ll alice_cnt=0,bob_cnt=0;

    ll acurrent=alice_time[0];
    ll bcurrent= bob_time[0];
    ll cnt=0;
    ll i=0,j=0;

    while(cnt<chocolates){
        if(acurrent>bcurrent){
            j++;
            cnt++;
            bob_cnt++;
            bcurrent+=bob_time[j];
        }
        else{
            i++;
            cnt++;
            alice_cnt++;
            acurrent+=alice_time[i];
        }        
    }


    cout<<alice_cnt<<" "<<bob_cnt<<endl;


}



int main(){

    solve();
    
}