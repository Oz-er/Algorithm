#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll timer_cnt = 1;

void dfs(ll node, vector<vector<ll>> &graph, vector<ll> &disc, vector<ll> &low, stack<ll> &st, vector<bool> &in_stack, vector<vector<ll>> &all_sccs)
{

    // mark discovery and low times and hten push current component

    disc[node] = low[node] = timer_cnt;
    timer_cnt++;
    st.push(node);
    in_stack[node] = true;
    // Traverse all directed neighbors
    for (int nxt : graph[node])
    {

        // If the neighbor hasn't been visited yet
        if (disc[nxt] == -1)
        {
            dfs(nxt, graph, disc, low, st, in_stack, all_sccs);

            // On backtrack, update the lowest reachable node
            low[node] = min(low[node], low[nxt]);
        }
        // If the neighbor is already visited AND is currently in our active stack
        // This means we found a back-edge within our current component!
        else if (in_stack[nxt] == true)
        {
            low[node] = min(low[node], disc[nxt]);
        }
        // (If it's visited but NOT in the stack, it's a cross-edge to an already finalized SCC. We ignore it.)
    }

    if (low[node] == disc[node])
    {
        vector<ll> current_scc;

        while (true)
        {

            ll top_node = st.top();
            st.pop();
            in_stack[top_node] = false;
            current_scc.push_back(top_node);

            if (top_node == node)
            {
                break;
            }
        }
        all_sccs.push_back(current_scc);
    }
}

int main()
{

    ll nodes, edges;
    cin >> nodes >> edges;

    vector<vector<ll>> graph(nodes);

    for (ll i = 0; i < edges; i++)
    {
        ll u, v;
        cin >> u >> v;

        graph[u].push_back(v);
    }

    vector<ll> disc(nodes, -1);
    vector<ll> low(nodes, -1);

    stack<ll> st;
    vector<bool> in_stack(nodes, false);

    vector<vector<ll>> all_sccs;

    for (ll i = 0; i < nodes; i++)
    {

        if (disc[i] == -1)
        {
            dfs(i, graph, disc, low, st, in_stack, all_sccs);
        }
    }

    cout << "\nStrongly Connected Components (SCCs) found: " << all_sccs.size() << endl;
    for (int i = 0; i < all_sccs.size(); i++)
    {
        cout << "SCC " << i + 1 << ": ";
        for (int node : all_sccs[i])
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
/* =========================================
SAMPLE INPUT 
(A graph with 8 nodes and 3 distinct components)
=========================================
8
9
0 1
1 2
2 0
2 3
3 4
4 5
5 3
6 5
6 7

=========================================
EXPECTED OUTPUT:
=========================================
Strongly Connected Components (SCCs) found: 4
SCC 1: 5 4 3 
SCC 2: 2 1 0 
SCC 3: 7 
SCC 4: 6 
=========================================
*/