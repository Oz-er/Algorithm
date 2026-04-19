#include<bits/stdc++.h>
using namespace std;
    




void Building_table(vector<int>&price,vector<vector<int>>&dp){


    int size=dp.size()-1;
    for (int i=0;i<=size;i++)dp[i][0] = 0;
    for (int j=0;j<=size;j++)dp[0][j] = 0;

    for(int i=1;i<=size;i++){
        for(int j=1;j<=size;j++){
            if(i>j){
                dp[i][j]=dp[i-1][j];
            }
            else{
                dp[i][j]=max(dp[i-1][j],price[i-1]+dp[i][j-i]);
            }
        }
    }
}



vector<int> calculate_pieces(vector<vector<int>>&dp, vector<int>&price){

    vector<int>pieces;

    int col = dp.size()-1;
    int row = price.size();

    int i =row;
    int j =col;

    while(i>0 && j>0){
        if(dp[i][j]!=dp[i-1][j]){
            pieces.push_back(i);
            j-=i;
        }
        else{
            i--;
        }
    }

    return pieces;

}




int main(){

    int n;
    cin>>n;
    
    vector<int>price(n);

    vector<vector<int>>dp(n+1,vector<int>(n+1));
    

    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        price[i] = a;
    }


    Building_table(price,dp);

    cout<<"max value :"<<dp[n][n]<<endl;


    vector<int>pieces;

    pieces = calculate_pieces(dp,price);

    cout << "Pieces used: ";
    for (int p : pieces) cout << p << " ";
    cout << endl;
}





/* =========================================
SAMPLE INPUT 
(Rod length 4, prices for lengths 1, 2, 3, 4)
=========================================
4
1 5 8 9
=========================================
EXPECTED OUTPUT:
=========================================
max value : 10
Pieces used: 2 2 
(Note: Optimal revenue is achieved by cutting two pieces of length 2)
=========================================
*/