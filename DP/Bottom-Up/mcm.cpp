#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Recursive function to print optimal parenthesis structure
void print_parens(vector<vector<int>>& s, int i, int j){
    if(i == j){
        cout << "A" << i;
    }
    else{
        cout << "(";
        print_parens(s, i, s[i][j]);
        print_parens(s, s[i][j]+1, j);
        cout << ")";
    }
}


void Building_table(vector<int>& p, vector<vector<int>>& m, vector<vector<int>>& s){
    int n = p.size() - 1; 

    for(int i=1;i<=n;i++) m[i][i] = 0;

    for(int l=2;l<=n;l++){ // l is the chain length
        for(int i=1;i<=n-l+1;i++){
            int j = i+l-1;
            m[i][j] = INF;
            
            for(int k=i;k<=j-1;k++){
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}


int main(){
    int n; // number of matrices
    cin >> n;
    
    // Dimension array p has size n+1
    vector<int> p(n+1);
    for(int i=0;i<=n;i++){
        cin >> p[i];
    }

    vector<vector<int>> m(n+1, vector<int>(n+1));
    vector<vector<int>> s(n+1, vector<int>(n+1));

    Building_table(p, m, s);

    cout << "Minimum Cost: " << m[1][n] << endl;
    cout << "Optimal Parenthesization: ";
    print_parens(s, 1, n);
    cout << endl;
}