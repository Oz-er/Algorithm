#include<bits/stdc++.h>
using namespace std;

// Returns a vector of pairs, where each pair is {height, width} of a piece sold
vector<pair<int,int>> trackback(vector<vector<pair<int,int>>>& s, int m, int n){
    vector<pair<int,int>> pieces;
    int curr_h = m;
    int curr_w = n;

    // 0 = Sell as is
    // 1 = Horizontal Cut (stores cut height k)
    // 2 = Vertical Cut (stores cut width k)

    while(curr_h > 0 && curr_w > 0){
        int type = s[curr_h][curr_w].first;
        int k = s[curr_h][curr_w].second;

        if(type == 0){
            // Best option is to sell this specific piece as is
            pieces.push_back({curr_h, curr_w});
            break; // No remainder left, we sold the whole remaining block
        }
        else if(type == 1){
            // Horizontal cut: we sold the top part of height k
            pieces.push_back({k, curr_w});
            // Remainder is the bottom part
            curr_h -= k;
        }
        else if(type == 2){
            // Vertical cut: we sold the left part of width k
            pieces.push_back({curr_h, k});
            // Remainder is the right part
            curr_w -= k;
        }
    }
    return pieces;
}


void Building_table(int m, int n, vector<vector<int>>& price, 
                    vector<vector<int>>& dp, 
                    vector<vector<pair<int,int>>>& s){
    
    // Fill DP table
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            // Option 0: Sell piece i x j as is
            int max_val = price[i][j];
            s[i][j] = {0, 0}; // Default: No cut

            // Option 1: Horizontal Cuts
            // Cut at height k (1 to i-1). Sell top (k x j), optimize remainder ((i-k) x j)
            for(int k=1;k<i;k++){
                int current_val = price[k][j] + dp[i-k][j];
                if(current_val > max_val){
                    max_val = current_val;
                    s[i][j] = {1, k}; // Type 1 (Horizontal), Cut at k
                }
            }

            // Option 2: Vertical Cuts
            // Cut at width k (1 to j-1). Sell left (i x k), optimize remainder (i x (j-k))
            for(int k=1;k<j;k++){
                int current_val = price[i][k] + dp[i][j-k];
                if(current_val > max_val){
                    max_val = current_val;
                    s[i][j] = {2, k}; // Type 2 (Vertical), Cut at k
                }
            }

            dp[i][j] = max_val;
        }
    }
}


int main(){
    int m, n;
    // Dimensions of the chocolate (Height m, Width n)
    cin >> m >> n;

    // Price table. Using 1-based indexing
    vector<vector<int>> price(m+1, vector<int>(n+1));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin >> price[i][j];
        }
    }

    vector<vector<int>> dp(m+1, vector<int>(n+1));
    // s table stores {Type, CutPosition}
    vector<vector<pair<int,int>>> s(m+1, vector<pair<int,int>>(n+1));

    Building_table(m, n, price, dp, s);

    cout << "Max Revenue: " << dp[m][n] << endl;

    vector<pair<int,int>> pieces = trackback(s, m, n);

    cout << "Pieces sold (Height x Width):" << endl;
    for(auto p : pieces){
        cout << p.first << " " << p.second << endl;
    }
}