#include<bits/stdc++.h>
using namespace std;
#define ll long long 





string s="";

void dfs(vector<vector<char>>&v,int r,int c,int n,int m,    vector<vector<ll>> &visited) {



    if(r<0 || r>=n || c<0 || c>=m) return; 
    if(v[r][c]=='#') return;
    if(v[r][c]=='B') return;

    if(visited[r][c])return;

    visited[r][c]=1;

    if(v[r-1][c]=='.' && visited[r-1][c]==1){
        s+='D';
        dfs(v,r-1,c,n,m,visited);
    }

    if(v[r+1][c]=='.' && visited[r+1][c]==1){
        s+='U';
        dfs(v,r+1,c,n,m,visited);
    }
    if(v[r][c-1]=='.'&& visited[r][c-1]==1){
        s+='L';
        dfs(v,r,c-1,n,m,visited);
    }
    if(v[r][c+1]=='.'&& visited[r][c+1]==1){
        s+='R';
        dfs(v,r,c+1,n,m,visited);
    }


}


int main(){
    ll n,m;
    cin>>n>>m;


    vector<vector<char>> v(n,vector<char>(m));

    vector<vector<ll>> visited(n,vector<ll>(m));


    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            visited[i][j]=0;
            }
    }


    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>v[i][j];
        }
    }

    ll row,col;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(v[i][j]=='A'){
                row=i;
                col=j;
            }
        }
    }





}

