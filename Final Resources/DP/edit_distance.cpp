#include<bits/stdc++.h>
using namespace std;

void trackback(vector<vector<int>>& dp, string& s1, string& s2){
    int i = s1.size();
    int j = s2.size();
    vector<string> ops;

    while(i>0 && j>0){
        if(s1[i-1] == s2[j-1]){
            i--; 
            j--;
        }
        else if(dp[i][j] == dp[i-1][j-1] + 1){
            ops.push_back("Replace " + string(1, s1[i-1]) + " with " + string(1, s2[j-1]));
            i--; 
            j--;
        }
        else if(dp[i][j] == dp[i-1][j] + 1){
            ops.push_back("Delete " + string(1, s1[i-1]));
            i--;
        }
        else if(dp[i][j] == dp[i][j-1] + 1){
            ops.push_back("Insert " + string(1, s2[j-1]));
            j--;
        }
    }
    while(i > 0){
        ops.push_back("Delete " + string(1, s1[i-1]));
        i--;
    }
    while(j > 0){
        ops.push_back("Insert " + string(1, s2[j-1]));
        j--;
    }

    reverse(ops.begin(), ops.end());

    for(int k=0; k<ops.size(); k++){
        cout << ops[k] << endl;
    }
}


void Building_table(string& s1, string& s2, vector<vector<int>>& dp){
    int n = s1.size();
    int m = s2.size();

    for(int i=0;i<=n;i++) dp[i][0] = i;
    for(int j=0;j<=m;j++) dp[0][j] = j;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                dp[i][j] = 1 + min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]});
            }
        }
    }
}

void printtable(vector<vector<int>>& dp){
        int n =dp.size();
        int m = dp[0].size();
        for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
}


int main(){
    string s1, s2;
    cin >> s1 >> s2;

    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1));

    Building_table(s1, s2, dp);

    cout << "Edit Distance: " << dp[n][m] << endl;
    cout << "Operations: " << endl;
    trackback(dp, s1, s2);


}


/* =========================================
SAMPLE INPUT 
(Two strings: kitten and sitting)
=========================================
kitten
sitting
=========================================
EXPECTED OUTPUT:
=========================================
Edit Distance: 3
Operations: 
Insert g
Replace e with i
Replace k with s

=========================================
*/