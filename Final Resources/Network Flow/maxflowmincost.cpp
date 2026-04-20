#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;



//This code repeatedly finds the cheapest available augmenting path in a residual graph and pushes flow until no path remains, producing maximum flow with minimum total cost.



//-------------------- Bellman-Ford (shortest cost path in residual graph) --------------------

bool bellman_ford(vector<vector<ll>> &g,
                  vector<vector<ll>> &capacity,
                  vector<vector<ll>> &cost,
                  ll source,
                  ll sink,
                  vector<ll> &parent)
{
    ll n = g.size();
    vector<ll> dist(n, INF);

    dist[source] = 0;
    parent[source] = -1;

    for(int i = 0; i < n - 1; i++){
        for(int u = 0; u < n; u++){

            if(dist[u] == INF) continue;

            for(auto v : g[u]){
                if(capacity[u][v] > 0 &&
                   dist[v] > dist[u] + cost[u][v]){

                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    return dist[sink] != INF;
}

//-------------------- Min Cost Max Flow --------------------

pair<ll,ll> mcmf(vector<vector<ll>> &g,
                 vector<vector<ll>> &capacity,
                 vector<vector<ll>> &cost,
                 ll source,
                 ll sink)
{
    ll n = g.size();

    ll max_flow = 0;
    ll min_cost = 0;

    vector<ll> parent(n);

    while(bellman_ford(g, capacity, cost, source, sink, parent)){

        ll path_flow = INF;

        //---------------- find bottleneck ----------------
        for(ll v = sink; v != source; v = parent[v]){
            ll u = parent[v];
            path_flow = min(path_flow, capacity[u][v]);
        }

        //---------------- update residual graph ----------------
        for(ll v = sink; v != source; v = parent[v]){
            ll u = parent[v];

            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;

            min_cost += path_flow * cost[u][v];
        }

        max_flow += path_flow;
    }

    return {max_flow, min_cost};
}


int main(){

    ll nodes, edges;
    cin >> nodes >> edges;

    vector<vector<ll>> g(nodes);
    vector<vector<ll>> capacity(nodes, vector<ll>(nodes, 0));
    vector<vector<ll>> cost(nodes, vector<ll>(nodes, 0));

    for(int i = 0; i < edges; i++){

        ll u, v, cap, c;
        cin >> u >> v >> cap >> c;

        g[u].push_back(v);
        g[v].push_back(u);

        capacity[u][v] += cap;

        cost[u][v] = c;
        cost[v][u] = -c;
    }

    ll source, sink;
    cin >> source >> sink;

    auto result = mcmf(g, capacity, cost, source, sink);

    cout << "Maximum possible flow is: " << result.first << endl;
    cout << "Minimum cost for this flow is: " << result.second << endl;

    return 0;
}



/* =========================================
SAMPLE INPUT 
4 nodes, 5 edges
Format: u v capacity cost
=========================================
4 5
0 1 2 1
0 2 1 2
1 2 1 1
1 3 1 3
2 3 2 1
0
3

=========================================
EXPECTED OUTPUT:
=========================================
Maximum possible flow is: 2
Minimum cost for this flow is: 6
=========================================
*/