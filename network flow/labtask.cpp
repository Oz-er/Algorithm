#include<bits/stdc++.h>
using namespace std;

int nodes;


bool bfs(vector<vector<int>> &graph, int source, int target, vector<int> &parent){
    
    int nodes = graph.size();
    vector<bool>visited(nodes,false);
    
    queue<int>q;
    q.push(source);
    parent[source]=-1;
    visited[source]=true;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int v=0;v<nodes;v++){
            if(visited[v]==false && graph[u][v] > 0){
                
                if(v==target){
                    parent[v]=u;
                    return true;
                }
                
                visited[v]=true;
                parent[v]=u;
                q.push(v);
            }
        }
    }

    return false;

}


int fordFulkerson(vector<vector<int>> &graph, int source, int target){
    
    int u,v;
    int nodes = graph.size();

    vector<vector<int>>rGraph(nodes,vector<int>(nodes));

    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            rGraph[i][j]=graph[i][j];
        }
    }

    vector<int>parents(nodes);

    int max_flow=0;


    while(bfs(rGraph,source,target,parents)){

        int path_flow = INT_MAX;

        for(v=target;v!=source;v=parents[v]){
            u=parents[v];
            path_flow=min(path_flow,rGraph[u][v]);
        }

        for(v=target;v!=source;v=parents[v]){
            u=parents[v];
            rGraph[u][v]-=path_flow;
            rGraph[v][u]+=path_flow;
        }   

        max_flow+=path_flow;
    }

    return max_flow;

}



int main(){

    int source,target,edges;

    // cout<<"enter the number of nodes"<<endl;
    cin>>nodes;


    // cout<<"source node : ";
    cin>>source;


    // cout<<"target node : ";
    cin>>target;


    // cout<<"enter the number of edges :";
    cin>>edges;

    vector<vector<int>>graph(nodes,vector<int>(nodes));
    

    for(int i=0;i<edges;i++){
        int from,to,value;
        cin>>from>>to>>value;
        graph[from-1][to-1]=value;
    }


    // for(int i=0;i<nodes;i++){
    //     for(int j=0;j<nodes;j++){
    //         cout<<graph[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }


    int maxflow = fordFulkerson(graph,source-1,target-1);
    cout<<maxflow<<endl;




}