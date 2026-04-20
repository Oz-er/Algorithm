#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

// Returns {minimum_tour_cost, optimal_city_sequence}
pair<ll, vector<ll>> traveling_salesman(ll n, const vector<vector<ll>> &cost) {
    
    // dp[mask][i] = min cost to visit the subset of cities represented by 'mask', ending at city 'i'
    // A mask of 5 (binary 101) means city 0 and city 2 have been visited.
    vector<vector<ll>> dp(1 << n, vector<ll>(n, INF));
    vector<vector<ll>> parent(1 << n, vector<ll>(n, -1));

    //------------------- Phase 1: Base Case Initialization -----------------------------
    // We arbitrarily start our tour at City 0. 
    // The mask is 1 (binary 000...001), meaning only City 0 is visited.
    dp[1][0] = 0;

    //------------------- Phase 2: DP Bitmask Transitions -----------------------------
    for (ll mask = 1; mask < (1 << n); mask++) {
        for (ll u = 0; u < n; u++) {
            
            // If city 'u' is NOT in the current mask, we can't transition from it
            if (!(mask & (1 << u))) continue;

            // Try to travel from city 'u' to an unvisited city 'v'
            for (ll v = 0; v < n; v++) {
                
                // If city 'v' is ALREADY in the mask, or there is no path, skip it
                if ((mask & (1 << v)) || cost[u][v] == INF) continue;

                // Create the new state by turning on the 'v' bit
                ll next_mask = mask | (1 << v);
                ll new_cost = dp[mask][u] + cost[u][v];

                // If we found a cheaper way to reach this state, update it
                if (new_cost < dp[next_mask][v]) {
                    dp[next_mask][v] = new_cost;
                    parent[next_mask][v] = u; // Remember we arrived at 'v' from 'u'
                }
            }
        }
    }

    //------------------- Phase 3: Completing the Cycle and Backtracking ----------------
    ll min_tour_cost = INF;
    ll best_last_city = -1;
    ll full_mask = (1 << n) - 1; // All bits are 1 (all cities visited)

    // Find the best city to return home (City 0) from
    for (ll u = 1; u < n; u++) {
        if (dp[full_mask][u] != INF && cost[u][0] != INF) {
            ll current_tour_cost = dp[full_mask][u] + cost[u][0];
            
            if (current_tour_cost < min_tour_cost) {
                min_tour_cost = current_tour_cost;
                best_last_city = u;
            }
        }
    }

    vector<ll> tour;
    
    // If no valid cycle exists (graph is disconnected)
    if (min_tour_cost == INF) {
        return {INF, tour}; 
    }

    // Backtrack from the best last city back to City 0
    ll curr_mask = full_mask;
    ll curr_city = best_last_city;

    while (curr_city != -1) {
        tour.push_back(curr_city);
        ll prev_city = parent[curr_mask][curr_city];
        
        // Remove the current city from the mask by flipping its bit to 0 using XOR
        curr_mask = curr_mask ^ (1 << curr_city); 
        curr_city = prev_city;
    }

    // The backtrack built the path backwards (from last city down to 0)
    reverse(tour.begin(), tour.end());

    // Append City 0 to the very end to complete the round-trip cycle
    tour.push_back(0);

    return {min_tour_cost, tour};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    vector<vector<ll>> cost(n, vector<ll>(n));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> cost[i][j];
            // In CP, a self-loop cost of 0 is fine, but disconnected edges 
            // are often inputted as -1. We convert them to INF for the algorithm.
            if (cost[i][j] == -1) {
                cost[i][j] = INF;
            }
        }
    }

    pair<ll, vector<ll>> result = traveling_salesman(n, cost);
    ll min_cost = result.first;
    vector<ll> optimal_tour = result.second;

    if (min_cost == INF) {
        cout << "No valid TSP tour exists.\n";
    } else {
        cout << "Minimum Tour Cost: " << min_cost << "\n";
        cout << "Optimal Route: ";
        for (ll i = 0; i < optimal_tour.size(); i++) {
            if (i > 0) cout << " -> ";
            cout << optimal_tour[i];
        }
        cout << "\n";
    }

    return 0;
}

/* =========================================
SAMPLE INPUT 
(4 Cities. Distance matrix where -1 means no direct road)
=========================================
4
 0 10 15 20
10  0 35 25
15 35  0 30
20 25 30  0

=========================================
EXPECTED OUTPUT:
=========================================
Minimum Tour Cost: 80
Optimal Route: 0 -> 1 -> 3 -> 2 -> 0
=========================================
*/