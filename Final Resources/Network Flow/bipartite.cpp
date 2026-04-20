#include<bits/stdc++.h>
using namespace std;

bool bfs(vector<vector<int>>& rGraph, int source, int target, vector<int>& parent) {
    int n = rGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    parent[source] = -1;
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == target) { parent[v] = u; return true; }
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>>& graph, int source, int target,
                  vector<vector<int>>& rGraph) {   // rGraph passed out so we can read it
    int n = graph.size();
    rGraph = graph;                                 // initialise residual = original
    vector<int> parent(n);
    int max_flow = 0;

    while (bfs(rGraph, source, target, parent)) {
        int path_flow = INT_MAX;
        for (int v = target; v != source; v = parent[v])
            path_flow = min(path_flow, rGraph[parent[v]][v]);
        for (int v = target; v != source; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    int g1, g2, edges;
    cin >> g1 >> g2 >> edges;

    // Node layout:
    //   0           → supersource (s)
    //   1..g1       → Applicants  (Group 1)
    //   g1+1..g1+g2 → Jobs        (Group 2)
    //   g1+g2+1     → supersink   (t)
    int total = g1 + g2 + 2;
    int s = 0, t = g1 + g2 + 1;

    vector<vector<int>> graph(total, vector<int>(total, 0));

    // s → every applicant, capacity 1
    for (int i = 1; i <= g1; i++)
        graph[s][i] = 1;

    // every job → t, capacity 1
    for (int j = g1 + 1; j <= g1 + g2; j++)
        graph[j][t] = 1;

    // Compatible pairs: applicant u → job v, capacity 1
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][g1 + v] = 1;
    }

    vector<vector<int>> rGraph;
    int matched = fordFulkerson(graph, s, t, rGraph);

    cout << "Maximum number of applicants matched: " << matched << "\n";
    cout << "Matching Details:\n";

    // Read the matching: applicant i (node i) is matched to job j (node g1+j)
    // when the original edge had capacity 1 AND residual is now 0 (flow was used)
    for (int i = 1; i <= g1; i++) {
        for (int j = g1 + 1; j <= g1 + g2; j++) {
            if (graph[i][j] == 1 && rGraph[i][j] == 0) {
                cout << "Applicant " << i
                     << " was assigned to Job " << (j - g1) << "\n";
            }
        }
    }

    return 0;
}

/*
=========================================
SAMPLE INPUT
(4 applicants, 3 jobs, 6 compatible pairs)
Format:
g1 g2 edges
u v  (u = applicant 1-indexed, v = job 1-indexed)

4 3 6
1 2
2 1
3 1
3 2
4 3
4 1

=========================================
EXPECTED OUTPUT:
=========================================
Maximum number of applicants matched: 3
Matching Details:
Applicant 1 was assigned to Job 2
Applicant 2 was assigned to Job 1
Applicant 4 was assigned to Job 3
=========================================
NOTE: Applicant 3 is unmatched because both Job 1 and Job 2
were already taken by Applicants 2 and 1 respectively.
=========================================
*/