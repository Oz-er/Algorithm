#include <bits/stdc++.h>
using namespace std;

#define MAX 100
#define KEYS 12

int keypad[KEYS][3] = {
    {0, 0, 1},
    {0, 1, 2},
    {0, 2, 3},
    {1, 0, 4},
    {1, 1, 5},
    {1, 2, 6},
    {2, 0, 7},
    {2, 1, 8},
    {2, 2, 9},
    {3, 0, -1},  
    {3, 1, 0},    
    {3, 2, -2}    
};

int dp[MAX][KEYS][KEYS];
vector<int> digits;
int n;

int keyIndex(char c) {
    if (c >= '1' && c <= '9')
        return c - '1';
    if (c == '*')
        return 9;
    if (c == '0')
        return 10;
    if (c == '#')
        return 11;
    return -1;
}

int euclideanDistance(int a, int b) {
    int dx = keypad[a][0] - keypad[b][0];
    int dy = keypad[a][1] - keypad[b][1];
    double d = sqrt(dx * dx + dy * dy);
    return (int) round(d * 2.0);
}

int solve(int i, int f1, int f2) {
    if (i == n)
        return 0;

    if (dp[i][f1][f2] != -1)
        return dp[i][f1][f2];

    int d = digits[i];

    int cost1 = euclideanDistance(f1, d) + solve(i + 1, d, f2);
    int cost2 = euclideanDistance(f2, d) + solve(i + 1, f1, d);

    dp[i][f1][f2] = min(cost1, cost2);
    return dp[i][f1][f2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        string number;
        cin >> number;

        n = number.length();
        digits.resize(n);

        for (int i = 0; i < n; i++)
            digits[i] = keyIndex(number[i]);

        memset(dp, -1, sizeof(dp));

        int start1 = 9;   
        int start2 = 11;  

        int result = solve(0, start1, start2);

        cout << "Test Case " << tc << ":\n";
        cout << fixed << setprecision(1);
        cout << "Min effort: " << result / 2.0 << "\n";
    }
    return 0;
}
