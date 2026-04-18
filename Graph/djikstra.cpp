#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=1e18;


pair<vector<ll>,vector<ll>> djikstra(vector<vector<pair<ll,ll>>> &g, ll starting_node){

    ll n = g.size();
    priority_queue<pair<ll,ll> ,
                   vector<pair<ll,ll>> ,
                   greater<pair<ll,ll>>> pq;






    vector<ll> distance_from_source(n,INF);
    vector<ll>parent(n,-1);


    distance_from_source[starting_node]=0;
    pq.push({0,starting_node});


    while(!pq.empty()){


        pair<ll,ll> p = pq.top();
        pq.pop();
        ll w = p.first; //1
        ll nxt = p.second; //v4

        if(w>distance_from_source[nxt]){ //1<INF
            continue;
        }

        for(auto &p : g[nxt]){
            ll wt = p.first;   //4
            ll nt = p.second;   //v7

            if(distance_from_source[nt]>wt+w){
                distance_from_source[nt]= w+wt;
                pq.push({distance_from_source[nt],nt});

                parent[nt] = nxt;
            }
        }
    }


    return {distance_from_source,parent};
}





vector<ll> get_path(vector<ll> &parent , ll target_node){

    vector<ll> path;

    while(target_node!=-1){
        path.push_back(target_node);
        target_node = parent[target_node];
    }

    reverse(path.begin(),path.end());
    return path;
}


int main(){

    ll nodes,edges;
    cin>>nodes>>edges;
    vector<vector<pair<ll,ll>>> graph(nodes);


    for(int i=0;i<edges;i++){
    ll node1,node2,weight;
    cin>>node1>>node2>>weight;
    graph[node1].push_back({weight,node2});
    graph[node2].push_back({weight,node1});
    }


    ll starting_node;
    cin>>starting_node;
    
    ll target_node;
    cin>>target_node;


    pair<vector<ll>,vector<ll>> distance_and_parent;
    distance_and_parent=djikstra(graph,starting_node);


    vector<ll> shortest_paths = distance_and_parent.first;
    vector<ll> parents = distance_and_parent.second;


    for(int i=0;i<nodes;i++){
    cout<<i<<" : "<< shortest_paths[i]<<endl;
    }

    vector<ll> path;
    path = get_path(parents,target_node);

    cout<<"shortest path for the desired node is"<<endl;

    for(int i=0;i<path.size();i++){
        if(i)cout << " -> ";
        cout<<path[i];
    }

    cout<<endl;




}






// 7 12
// 0 1 2
// 0 3 1
// 1 3 3
// 1 4 10
// 2 0 4
// 2 5 5
// 3 2 2
// 3 5 8
// 3 6 3
// 3 4 2
// 4 6 6
// 6 5 1
// 0
// 6
