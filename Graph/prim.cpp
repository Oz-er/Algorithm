#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF =1e18;


int main(){

    ll nodes,edges;
    cin>>nodes>>edges;

    nodes++;


    vector<vector<pair<ll,ll>>> each(nodes);


    for(int i=0;i<edges;i++){
        ll node1,node2,weight;
        cin>>node1>>node2>>weight;
        each[node1].push_back({node2,weight});
        each[node2].push_back({node1,weight});
    }

    vector<ll>costs(nodes,INF);
    vector<ll>parent(nodes,-1);


    bool stop=false;
    ll minNode=1;
    ll minCost=INF;

    while(!stop){
        stop =true;


        for(ll i=1;i<nodes;i++){
            if(costs[i]==INF){
                stop=false;
                if(minCost>costs[i]){
                    minCost=costs[i];
                    minNode=i;
                }
            }
        }

        if(stop)break;

        vector<pair<ll,ll>> w= each

    }

}