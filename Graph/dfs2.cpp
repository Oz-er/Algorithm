#include<bits/stdc++.h>
using namespace std;


void dfs(vector<vector<int>>&back,
vector<vector<int>>&graph,vector<int>&v,vector<int>&order,int node){
    v[node]=1;
    order.push_back(node);

    for(int nxt : graph[node]){
        if(!v[nxt]){
            dfs(back,graph,v,order,nxt);
        }

        else{
            back[node].push_back(nxt);
        }
    }


}



int main(){
    int vertices,edges;

    cout<<"Enter num of vertices : ";
    cin>>vertices;
    cout<<endl;

    cout<<"Enter num of edges: ";
    cin>>edges;
    cout<<endl;

    vector<vector<int>>graph(vertices);

    cout<<"enter the edges :"<<endl;


    for(int i=0;i<edges;i++){
        int a,b;
        cin>>a>>b;

        if(a>=vertices || b>=vertices || a<0 || b<0){
            cout<<"Invalid entry"<<endl;
            continue;
        } 

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int start;
    cout<< "Starting edge : "<<endl;
    cin>>start;
    cout<<endl;

    vector<int>visited(vertices,0);

    vector<int>storedfs;
    map<int,int>low;
    vector<vector<int>>back(vertices);


    dfs(back,graph,visited,storedfs,start);

    cout << "\nDFS Order: ";
    for (int x : storedfs) cout << x << " ";
    cout << endl;


    map<int,int>visitorder;


    int count = 1;
    for(int x : storedfs){
        visitorder[x]=count;
        count++;
    }



















}