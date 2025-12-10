#include<bits/stdc++.h>
using namespace std;

#define vertices 7
#define edges 10

#define WHITE 0
#define GREY 1
#define BLACK 2
#define INF 1e9


vector<vector<int>>graph(vertices,vector<int>(vertices));


vector<int>pre(vertices);
vector<int>color(vertices);
vector<int>discovery(vertices);
vector<int>finish(vertices);


vector<int>low(vertices);
vector<int>art;

int TIME=0;

void DFS_Visit(int u){

    color[u]=GREY;
    TIME+=1;
    discovery[u]=TIME;

    low[u]=discovery[u];

    int children=0;
    
    for(int x=0;x<vertices;x++){
        if(graph[u][x]){ 
                if(color[x]==WHITE){   //for tree edge
                pre[x]=u;
                children++;
        
                DFS_Visit(x);   

                if(low[x] >= discovery[u] && pre[u]!=-1){
                    art.push_back(u);
                }

                if(low[x] < low[u]){
                    low[u]=low[x];
                }
            }

            else if(color[x]==GREY && pre[u]!=x){   //for backedge
                if(low[u]>discovery[x]){
                    low[u]=discovery[x];
                }
            }
        }
    }

    if(pre[u] == -1 && children>1){     //for root
        art.push_back(u);
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

    cout<<"articulation points : "<<endl;

        for(int i=0;i<art.size();i++){

            cout<<art[i]<<" ";
        }

        cout<<endl;



    
}






    // for(int i=0;i<vertices;i++){
    //     cout<<discovery[i]<<" "<<finish[i];
    //     cout<<endl;
    // }

    // for(int i=0;i<backedge.size();i++){
    //     cout<<backedge[i].first<<" "<<backedge[i].second<<endl;
    // }





        // for(int i=0;i<vertices;i++){
        //     cout<<pre[i]<<" ";
        // }

        // cout<<endl;