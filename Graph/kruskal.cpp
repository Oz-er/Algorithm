#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

class DisjointSet{

private:
//quick recap of OOP encapsulation
// parent, rank = engine internals(private)
// find, unite = steering wheel + pedals(public)

vector<ll>parent;
vector<ll>rank;


public :

DisjointSet(ll n){
    parent.resize(n);
    rank.resize(n);
    
    for(int i=0;i<n;i++){
    parent[i]=i;
    rank[i]=1;
    }
    }


void make(ll v){
    parent[v]=v;
}


ll find(ll v){

    if(v==parent[v])return v;

    parent[v]=find(v);
    return parent[v];
}


void Union(ll a,ll b){
    a=find(a);
    b=find(b);

    if(a!=b){
        
    if(rank[a] < rank[b]){
    parent[a] = b;
    }
    else if(rank[a] > rank[b]){
    parent[b] = a;
    }
    else{
    parent[b] =a;
    rank[a]++;
    }
    }
}


};



bool comparator(vector<ll>&a , vector<ll> &b){
    return a[2]<b[2];
}



vector<tuple<ll,ll,ll>> Kruskal(vector<vector<ll>> &g){

    ll n = g.size();
    vector<tuple<ll,ll,ll>> tree;

    vector<vector<ll>> edges;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i<j && g[i][j]!=-1){
                edges.push_back({i,j,g[i][j]});
            }
        }
    }

    sort(edges.begin(),edges.end(),comparator);




    DisjointSet dsu(n);
   



    for(auto &e : edges){
    
    ll from = e[0];
    ll to = e[1];
    ll edge = e[2];

    if(dsu.find(from) != dsu.find(to)){
    dsu.Union(from,to);
    tree.push_back({from,to,edge});
    }

    }


    return tree;




}




int main(){

    ll nodes,e;
    cin>>nodes>>e;


    // vector<vector<pair<ll,ll>>>graph(nodes);

    vector<vector<ll>> graph(nodes, vector<ll>(nodes,-1));

    for(int i=0;i<e;i++){
    ll node1,node2,weight;
    cin>>node1>>node2>>weight;

    graph[node1][node2]=weight;
    graph[node2][node1]=weight;
    
    // graph[node1].push_back({node2,weight});
    // graph[node2].push_back({node1,weight});
    

    }



    vector<tuple<ll,ll,ll>> tree = Kruskal(graph);

    ll totalcost=0;

    for(ll i=0;i<tree.size();i++){
    ll from = get<0>(tree[i]);
    ll to = get<1>(tree[i]);
    ll edge = get<2>(tree[i]);
    totalcost+=edge;
    cout<<from<<" "<<to<<" "<<edge<<endl;
    }  


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
