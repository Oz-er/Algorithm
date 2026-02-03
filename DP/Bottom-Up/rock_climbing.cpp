#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = 1e9;

// Function to print the path from Top to Bottom
void trackback(vector<vector<int>>& dp, int rows, int cols) {
    // 1. Find the starting point (minimum value in the top row)
    int min_val = INF;
    int best_col = -1;
    
    for (int j = 0; j < cols; j++) {
        if (dp[0][j] < min_val) {
            min_val = dp[0][j];
            best_col = j;
        }
    }

    cout << "Path (Row, Col): ";
    
    // 2. Trace downwards
    int curr_col = best_col;
    for (int i = 0; i < rows; i++) {
        cout << "(" << i << ", " << curr_col << ") ";
        
        // Stop if we are at the last row
        if (i == rows - 1) break;

        // Look at the children in the next row (i+1) to see where we came from
        // We are looking for the neighbor that gave us the value: dp[i][curr] - cost[i][curr]
        // But simpler: just find the min among valid neighbors in row i+1
        
        int next_row = i + 1;
        int best_next_col = -1;
        int min_next_val = INF;

        // Check Down-Left
        if (curr_col > 0) {
            if (dp[next_row][curr_col - 1] < min_next_val) {
                min_next_val = dp[next_row][curr_col - 1];
                best_next_col = curr_col - 1;
            }
        }
        // Check Down-Directly
        if (dp[next_row][curr_col] < min_next_val) {
            min_next_val = dp[next_row][curr_col];
            best_next_col = curr_col;
        }
        // Check Down-Right
        if (curr_col < cols - 1) {
            if (dp[next_row][curr_col + 1] < min_next_val) {
                min_next_val = dp[next_row][curr_col + 1];
                best_next_col = curr_col + 1;
            }
        }

        curr_col = best_next_col;
    }
    cout << endl;
}

void Building_table(vector<vector<int>>& cost, vector<vector<int>>& dp, int rows, int cols) {
    // 1. Initialize the last row (base case)
    // The cost to finish at the bottom row is just the cost of that cell
    for (int j = 0; j < cols; j++) {
        dp[rows - 1][j] = cost[rows - 1][j];
    }

    // 2. Fill the table from second-to-last row up to the top (row 0)
    for (int i = rows - 2; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {
            
            int down = dp[i + 1][j];
            
            int down_left = INF;
            if (j > 0) down_left = dp[i + 1][j - 1];

            int down_right = INF;
            if (j < cols - 1) down_right = dp[i + 1][j + 1];

            dp[i][j] = cost[i][j] + min({down, down_left, down_right});
        }
    }
}

int main() {
    int rows, cols;
    // Example Input:
    // 4 4
    // 1 2 3 4
    // 5 1 2 3
    // 9 8 1 2
    // 4 5 6 7
    cin >> rows >> cols;

    vector<vector<int>> cost(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> cost[i][j];
        }
    }

    vector<vector<int>> dp(rows, vector<int>(cols));

    Building_table(cost, dp, rows, cols);

    // The answer is the minimum value in the top row (row 0)
    int min_cost = INF;
    for (int j = 0; j < cols; j++) {
        if (dp[0][j] < min_cost) {
            min_cost = dp[0][j];
        }
    }

    cout << "Minimum Cost: " << min_cost << endl;

    trackback(dp, rows, cols);

    return 0;
}