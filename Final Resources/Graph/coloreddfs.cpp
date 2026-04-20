#include<bits/stdc++.h>
using namespace std;

#define WHITE 0
#define GREY 1
#define BLACK 2
#define INF 1e9

int vertices, edges;

vector<vector<int>> graph;
vector<int> pre, color, discovery, finish;
vector<pair<int,int>> forwardedge, backedge;

int TIME = 0;

void DFS_Visit(int u) {
    color[u] = GREY;
    TIME += 1;
    discovery[u] = TIME;

    for (int x = 0; x < vertices; x++) {
        if (graph[u][x]) {
            if (color[x] == WHITE) {
                pre[x] = u;
                forwardedge.push_back({u, x});
                DFS_Visit(x);
            }
            else if (color[x] == GREY && pre[u] != x) {
                backedge.push_back({u, x});
            }
        }
    }

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

    for (int i = 0; i < edges; i++) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    DFS();

    cout << "Back edges:" << endl;
    if (backedge.empty()) {
        cout << "(none)" << endl;
    } else {
        for (auto& e : backedge)
            cout << e.first << " -> " << e.second << endl;
    }

    cout << "\nTree edges:" << endl;
    for (auto& e : forwardedge)
        cout << e.first << " -> " << e.second << endl;

    return 0;
}

/*
=========================================
SAMPLE INPUT
Format: vertices edges
        u v  (repeated 'edges' times)
=========================================
4 4
0 1
1 2
2 0
2 3
=========================================
EXPECTED OUTPUT:
=========================================
Back edges:
2 -> 0

Tree edges:
0 -> 1
1 -> 2
2 -> 3
=========================================


=========================================
SAMPLE INPUT 2 — 4-cycle
=========================================
4 4
0 1
1 2
2 3
3 0
=========================================
EXPECTED OUTPUT:
=========================================
Back edges:
3 -> 0

Tree edges:
0 -> 1
1 -> 2
2 -> 3
=========================================


=========================================
SAMPLE INPUT 3 — two cycles
=========================================
6 7
0 1
1 2
2 0
2 3
3 4
4 5
5 3
=========================================
EXPECTED OUTPUT:
=========================================
Back edges:
2 -> 0
5 -> 3

Tree edges:
0 -> 1
1 -> 2
2 -> 3
3 -> 4
4 -> 5
=========================================
*/
