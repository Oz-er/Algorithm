#include<bits/stdc++.h>
using namespace std;

typedef long long ll;


vector<tuple<ll,ll,ll>> SpanningTree(vector<vector<pair<ll,ll>>> &g){

    ll n = g.size();
    vector<bool>visited(n,false);

    priority_queue<tuple<ll,ll,ll> ,
                   vector<tuple<ll,ll,ll>> ,
                   greater<tuple<ll,ll,ll>>> pq;


    vector<tuple<ll,ll,ll>> tree;


    pq.push({0,0,0});

    ll cost=0;





    while(!pq.empty()){
        
    auto p = pq.top();
    pq.pop();
    ll edge = get<0>(p);
    ll source = get<1>(p);
    ll target = get<2>(p);
    
    if(visited[target])continue;
    visited[target]=true;
    
    cost+=edge;
    tree.push_back({edge,source,target});
    
    for(auto q : g[target]){
    
    ll from = target;
    ll to = q.first;
    ll e = q.second;

    if(!visited[to]){
    pq.push({e,from,to});
    }
    }
    }


    return tree;

    
                   
}




int main(){

    ll nodes,edges;
    cin>>nodes>>edges;
    vector<vector<pair<ll,ll>>> graph(nodes);


    for(int i=0;i<edges;i++){
    ll node1,node2,weight;
    cin>>node1>>node2>>weight;
    graph[node1].push_back({node2,weight});
    graph[node2].push_back({node1,weight});
    }


    vector<tuple<ll,ll,ll>> tree = SpanningTree(graph);

    ll totalcost=0;

    for(ll i=0;i<tree.size();i++){
    ll edge = get<0>(tree[i]);
    totalcost+=edge;
    ll from = get<1>(tree[i]);
    ll to = get<2>(tree[i]);
    cout<<from<<" "<<to<<" "<<edge<<endl;
    }


    // cout<<totalcost<<endl;


}






// 0 1 8
// 0 2 12
// 1 2 13
// 1 3 25
// 1 4 9
// 2 3 14
// 2 6 21
// 3 4 20
// 3 5 8
// 3 7 12
// 3 6 12
// 3 8 16
// 4 5 19
// 5 7 11
// 6 8 11
// 7 8 9
