#include<bits/stdc++.h>
using namespace std;

#define vertices 4
#define edges 4

#define WHITE 0
#define GREY 1
#define BLACK 2
#define INF 1e9


vector<vector<int>>graph(vertices,vector<int>(vertices));


vector<int>pre(vertices);
vector<int>color(vertices);
vector<int>discovery(vertices);
vector<int>finish(vertices);


vector<pair<int,int>>forwardedge;
vector<pair<int,int>>backedge;


int TIME=0;

void DFS_Visit(int u){

    color[u]=GREY;
    TIME+=1;
    discovery[u]=TIME;

    
    for(int x=0;x<vertices;x++){
        if(graph[u][x]){ 
            if(color[x]==WHITE){
            pre[x]=u;
            forwardedge.push_back({u,x});  // storing the forward edge
        
            DFS_Visit(x);
            }

        else if(color[x]==GREY && pre[u]!=x){
            backedge.push_back({u,x});
            }
        }
    }

    color[u]=BLACK;
    TIME+=1;
    finish[u]=TIME;
}






void DFS(){

    for(int x=0; x<vertices; x++){
        color[x]=WHITE;
        pre[x]= -1;
        finish[x]=INF;
        discovery[x]=INF;
    }

    for(int x=0;x<vertices;x++){
        if(color[x]==WHITE){
            DFS_Visit(x);
        }
    }

}



int main(){

    for(int i=0;i<edges;i++){
        int a,b;
        cin>>a>>b;

        graph[a][b]=1;
        graph[b][a]=1;
    }


    DFS();

    // for(int i=0;i<vertices;i++){
    //     cout<<discovery[i]<<" "<<finish[i];
    //     cout<<endl;
    // }

    for(int i=0;i<backedge.size();i++){
        cout<<backedge[i].first<<" "<<backedge[i].second<<endl;
    }



    
}