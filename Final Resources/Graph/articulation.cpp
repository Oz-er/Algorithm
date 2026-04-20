#include<bits/stdc++.h>
using namespace std;

#define WHITE 0
#define GREY 1
#define BLACK 2
#define INF 1e9

int vertices, edges;

vector<vector<int>> graph;
vector<int> pre, color, discovery, finish, low;
vector<int> art;
int TIME = 0;

void DFS_Visit(int u) {
    color[u] = GREY;
    TIME += 1;
    discovery[u] = TIME;
    low[u] = discovery[u];

    int children = 0;

    for (int x = 0; x < vertices; x++) {
        if (graph[u][x]) {
            if (color[x] == WHITE) {
                pre[x] = u;
                children++;

                DFS_Visit(x);

                if (low[x] < low[u])
                    low[u] = low[x];

                if (low[x] >= discovery[u] && pre[u] != -1)
                    art.push_back(u);
            }
            else if (color[x] == GREY && pre[u] != x) {
                if (low[u] > discovery[x])
                    low[u] = discovery[x];
            }
        }
    }

    if (pre[u] == -1 && children > 1)
        art.push_back(u);

    color[u] = BLACK;
    TIME += 1;
    finish[u] = TIME;
}

void DFS() {
    for (int x = 0; x < vertices; x++) {
        color[x] = WHITE;
        pre[x] = -1;
        finish[x] = INF;
        discovery[x] = INF;
    }
    for (int x = 0; x < vertices; x++) {
        if (color[x] == WHITE)
            DFS_Visit(x);
    }
}

int main() {
    cin >> vertices >> edges;

    graph.assign(vertices, vector<int>(vertices, 0));
    pre.assign(vertices, -1);
    color.assign(vertices, WHITE);
    discovery.assign(vertices, INF);
    finish.assign(vertices, INF);
    low.assign(vertices, INF);

    for (int i = 0; i < edges; i++) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    DFS();

    // deduplicate — a node may be pushed multiple times
    sort(art.begin(), art.end());
    art.erase(unique(art.begin(), art.end()), art.end());

    cout << "Articulation points:" << endl;
    for (int v : art)
        cout << v << " ";
    cout << endl;

    return 0;
}



/* =========================================
SAMPLE INPUT 
(Fixed at 7 vertices and 10 edges as per #define)
The graph structure: 
Cycle (0,1,2) -> Bridge -> Cycle (3,4,5) -> Bridge -> Node 6
=========================================
0 1
1 2
2 0
2 3
3 4
4 5
5 3
5 6
0 1
3 4
=========================================
EXPECTED OUTPUT:
=========================================
articulation points : 
5 3 2 
=========================================
NOTES:
- Vertices 2, 3, and 5 are articulation points because:
  - Removing 5 disconnects node 6.
  - Removing 3 disconnects the (3,4,5) cycle from the rest.
  - Removing 2 disconnects the (0,1,2) cycle from the rest.
- The root (node 0) is not an articulation point because it only 
  has one child in the DFS tree.
- The order of output (5 3 2) occurs because the algorithm 
  identifies articulation points as it backtracks from the 
  deepest DFS calls.
=========================================
*/








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