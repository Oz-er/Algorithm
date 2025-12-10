#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graphAdj;
vector<int> visited;

vector<int>discovery;
vector<int>finish;


vector<int>low;


int time =0;




void dfs(int node) {
    visited[node] = 1;
    cout << node << " ";

    for(int nxt : graphAdj[node]) {
        if(!visited[nxt]) {
            dfs(nxt);
        }
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    graphAdj.resize(n + 1);
    visited.assign(n + 1, 0);

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graphAdj[a].push_back(b);
        graphAdj[b].push_back(a);   // remove this if directed graph
    }

    int start;
    cin >> start;

    dfs(start);
    cout<<endl;

    return 0;
}