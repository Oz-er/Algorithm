#include <bits/stdc++.h>
using namespace std;

#define MAX 100
#define KEYS 12


// {1, 1, 5} means key 5 is at row 1, column 1.

int keypad[12][3] = {
    {0, 0, 1},
    {0, 1, 2},
    {0, 2, 3},
    {1, 0, 4},
    {1, 1, 5},
    {1, 2, 6},
    {2, 0, 7},
    {2, 1, 8},
    {2, 2, 9},
    {3, 0, -1},//*
    {3, 1, 0},
    {3, 2, -2} //#
};

int dp[MAX][KEYS][KEYS];
int digits[MAX];
int n;




//-------------------------------------------------
//-------------------------------------------------

int keyIndex(char c) {
    if (c >= '1' && c <= '9') return c - '1';
    if (c == '*') return 9;
    if (c == '0') return 10;
    if (c == '#') return 11;
    return -1;
}
// '1' → 0
// '2' → 1
// '5' → 4
// '9' → 8
// '*' → 9
// '0' → 10
// '#' → 11
// digits[0] = 4;   // key 5
// digits[1] = 10;  // key 0

//---------------------------------------------------
//---------------------------------------------------





//---------------------------------------------------
//---------------------------------------------------

int euclideanDistance(int a, int b) {
    int dx = keypad[a][0] - keypad[b][0];
    int dy = keypad[a][1] - keypad[b][1];
    double d = sqrt(dx * dx + dy * dy);
    return (int)round(d * 2.0);
}
// 5 = (1,1)
// 0 = (3,1)

// So:

// dx = 1 - 3 = -2
// dy = 1 - 1 = 0
// distance = sqrt(4) = 2
//---------------------------------------------------
//---------------------------------------------------








int solve(int i, int f1, int f2) {
    
    //---------base case-------------------------
    if (i == n) return 0;
    //--------- memoization ---------------------
    if (dp[i][f1][f2] != -1) return dp[i][f1][f2];


    int d = digits[i];
    int cost1 = euclideanDistance(f1, d) + solve(i + 1, d, f2);
    int cost2 = euclideanDistance(f2, d) + solve(i + 1, f1, d);

    dp[i][f1][f2] = min(cost1, cost2);
    return dp[i][f1][f2];
}
//50
// dp[0][*][#]
// =
// min(
//   distance(*,5) + dp[1][5][#],
//   distance(#,5) + dp[1][*][5]
// )

int main() {
    int t;
    cin >> t;

    for (int tc = 0; tc < t; tc++) {
        string number;
        cin >> number;

        n = number.size();

        cout << "Test Case " << tc + 1 << ": \n";

        for (int i = 0; i < n; i++) {
            digits[i] = keyIndex(number[i]);
        }

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < KEYS; j++) {
                for (int k = 0; k < KEYS; k++) {
                    dp[i][j][k] = -1;
                }
            }
        }

        int start1 = 9;
        int start2 = 11;

        int result = solve(0, start1, start2);

        cout << fixed << setprecision(1);
        cout << "Min effort: " << result / 2.0 << "\n";
    }

    return 0;
}
