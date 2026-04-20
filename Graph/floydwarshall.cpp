#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const ll INF = 1e9;
 
void floydWarshall(vector<vector<ll>>& dp){
 
    ll n = dp.size();
 
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dp[i][k]!=INF && dp[k][j]!=INF){
                    dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]);
                }
            }
        }
    }
}


void printMat(vector<vector<ll>> &g){
    
    int n= g.size();

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]==INF){
                cout<<"INF ";
            }
            else{
                cout<<g[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}
 
int main(){
 
    ll n,e;
    cin>>n>>e;
 
    vector<vector<ll>> graph(n, vector<ll>(n, INF));
 
    for(int i=0;i<n;i++){
        graph[i][i]=0;
    }
 
    for(int i=0;i<e;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        graph[u][v]=w;
    }
 
    floydWarshall(graph);
 
    //------ print the shortest distance matrix ------
    cout<<"\nShortest distance matrix:\n\n";
    printMat(graph);
}
 
// 5 10
// 0 1 4
// 0 3 5
// 1 2 1
// 1 4 6
// 2 0 2
// 2 3 3
// 3 2 1
// 3 4 2
// 4 0 1
// 4 3 4
 