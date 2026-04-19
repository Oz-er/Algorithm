#include<bits/stdc++.h>
using namespace std;

string trackback(vector<vector<int>>& dp, vector<string>& s1, vector<string>& s2){
    string lcs = "";
    int i = s1.size(), j = s2.size();

    while(i > 0 && j > 0){
        if(s1[i-1] == s2[j-1]){
            lcs = s1[i-1] + " " + lcs;
            i--; j--;
        }
        else if(dp[i-1][j] > dp[i][j-1]){
            i--;
        }
        else{
            j--;
        }
    }
    return lcs;
}

void build(vector<string>& s1, vector<string>& s2, vector<vector<int>>& dp){
    int n = s1.size(), m = s2.size();

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
}

string readFile(const string& filename){
    ifstream file(filename);
    string content, line;

    while(getline(file, line)){
        content += line + " ";
    }
    return content;
}

vector<string> tokenize(string s){
    vector<string> words;
    stringstream ss(s);
    string word;

    while(ss >> word){
        for(char &c : word) c = tolower(c);
        words.push_back(word);
    }
    return words;
}

int main(){

    string text1 = readFile("file1.txt");
    string text2 = readFile("file2.txt");

    vector<string> s1 = tokenize(text1);
    vector<string> s2 = tokenize(text2);

    int n = s1.size(), m = s2.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    build(s1, s2, dp);

    cout << "LCS Length: " << dp[n][m] << endl;
    cout << "LCS: " << trackback(dp, s1, s2) << endl;
}