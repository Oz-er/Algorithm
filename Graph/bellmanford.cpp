#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=1e18;


pair<vector<ll>,vector<ll>> bellman_ford(ll vertices,vector<tuple<ll,ll,ll>> &edges, ll starting_node){

    //edges = {source,destination,weight}


    vector<ll> distance_from_source(vertices,INF);
    vector<ll>parent(vertices,-1);

    distance_from_source[starting_node]=0;


    for(int i=0;i<vertices-1;i++){
        for(auto &edge : edges){
            ll source = get<0>(edge);
            ll dest = get<1>(edge);
            ll weight =get<2>(edge);

            if(distance_from_source[source]!=INF &&
                distance_from_source[source] + weight < 
                distance_from_source[dest]){
    
            distance_from_source[dest]= distance_from_source[source]+ weight;
            parent[dest]=source;
            }
        }
    
    }


//-----------------------extra iteration for neg cycle-----------------------------

    for(auto &edge : edges){
        ll source = get<0>(edge);
        ll dest = get<1>(edge);
        ll weight = get<2>(edge);

        if(distance_from_source[source] != INF && 
            distance_from_source[source] + weight < 
            distance_from_source[dest]){
            
            
        cout << "Negative cycle detected\n";
        break;
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


//-----------------------------inputting graph,starting and target node--------------------------------------
    ll nodes,edge;
    cin>>nodes>>edge;
    vector<tuple<ll,ll,ll>>edges;    
    for(int i=0;i<edge;i++){
    ll node1,node2,weight;
    cin>>node1>>node2>>weight;
    edges.push_back({node1,node2,weight});
    }

    ll starting_node;
    cin>>starting_node;
    ll target_node;
    cin>>target_node;



//-----------------------------receiving the pair of vectors and seperating the shortest path and parents vector-------------

    pair<vector<ll>,vector<ll>> distance_and_parent;
    distance_and_parent=bellman_ford(nodes,edges,starting_node);
    vector<ll> shortest_paths = distance_and_parent.first;
    vector<ll> parents = distance_and_parent.second;


    for(int i=0;i<nodes;i++){
    cout<<i<<" : "<< shortest_paths[i]<<endl;
    }



//---------------------------------path printing-------------------------------------------------------
    vector<ll> path;
    if(target_node < 0 || target_node >= nodes){
    cout <<"invalid target node"<<endl;
    }
    else if(shortest_paths[target_node] == INF){
    cout <<"no path exists"<<endl;
    }
    else{
    path = get_path(parents,target_node);
    cout<<"shortest path for the desired node is"<<endl;
    
    for(int i=0;i<path.size();i++){
    if(i)cout << " -> ";
    cout<<path[i];
    }
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
