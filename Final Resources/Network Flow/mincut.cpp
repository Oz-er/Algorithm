#include<bits/stdc++.h>
using namespace std;

//---------------- BFS for augmenting path ----------------

bool bfs(vector<vector<int>> &rGraph, int source, int target, vector<int> &parent){

    int n = rGraph.size();
    vector<bool> visited(n,false);

    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while(!q.empty()){

        int u = q.front();
        q.pop();

        for(int v = 0; v < n; v++){

            if(!visited[v] && rGraph[u][v] > 0){

                parent[v] = u;
                visited[v] = true;
                q.push(v);

                if(v == target) return true;
            }
        }
    }

    return false;
}

//---------------- Max Flow (Edmonds–Karp) ----------------

int maxFlow(vector<vector<int>> graph, int source, int target,
            vector<vector<int>> &rGraph){

    int n = graph.size();
    rGraph = graph;

    vector<int> parent(n);
    int flow = 0;

    while(bfs(rGraph, source, target, parent)){

        int path_flow = INT_MAX;

        for(int v = target; v != source; v = parent[v]){
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for(int v = target; v != source; v = parent[v]){
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        flow += path_flow;
    }

    return flow;
}

//---------------- Find reachable (S set) ----------------

vector<bool> getReachable(vector<vector<int>> &rGraph, int source){

    int n = rGraph.size();
    vector<bool> visited(n,false);

    queue<int> q;
    q.push(source);
    visited[source] = true;

    while(!q.empty()){

        int u = q.front();
        q.pop();

        for(int v = 0; v < n; v++){

            if(!visited[v] && rGraph[u][v] > 0){
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return visited;
}

//---------------- Print S and T sets ----------------

void printSets(const vector<bool> &vis){

    int n = vis.size();

    cout << "\nS set (reachable): ";
    for(int i = 0; i < n; i++){
        if(vis[i]) cout << i+1 << " ";
    }

    cout << "\nT set (not reachable): ";
    for(int i = 0; i < n; i++){
        if(!vis[i]) cout << i+1 << " ";
    }

    cout << "\n";
}

//---------------- Min Cut edges ----------------

void printMinCut(vector<vector<int>> &graph,
                 const vector<bool> &vis){

    int n = graph.size();

    cout << "\nMin Cut edges:\n";

    for(int u = 0; u < n; u++){
        for(int v = 0; v < n; v++){

            if(vis[u] && !vis[v] && graph[u][v] > 0){
                cout << u+1 << " - " << v+1 << "\n";
            }
        }
    }
}

//---------------- MAIN ----------------

int main(){

    int nodes, source, target, edges;

    cin >> nodes >> source >> target >> edges;

    vector<vector<int>> graph(nodes, vector<int>(nodes,0));

    for(int i = 0; i < edges; i++){
        int u, v, c;
        cin >> u >> v >> c;
        graph[u-1][v-1] = c;
    }

    vector<vector<int>> rGraph;

    int flow = maxFlow(graph, source-1, target-1, rGraph);

    cout << "Max Flow: " << flow << endl;

    vector<bool> vis = getReachable(rGraph, source-1);

    printSets(vis);
    printMinCut(graph, vis);

    return 0;
}