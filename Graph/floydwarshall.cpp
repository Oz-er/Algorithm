//task : transitice closure : warshall

#include<bits/stdc++.h>
using namespace std;

const int INF = 1000; 



int mat[5][5]={
        {0, 4, INF, 5, INF},
        {INF, 0, 1, INF, 6},
        {2, INF, 0, 3, INF},
        {INF, INF, 1, 0, 2},
        {1, INF, INF, 4, 0}
    };

int main(){


    int dp[5][5];
    
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            dp[i][j]=mat[i][j];
        }
    }
    
    for(int k=0;k<5;k++){
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){

                if(i!=k && j!=k){

                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
                }

            }
        }
    }



    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<dp[i][j]<<" ";
        }

        cout<<endl;
    }
}


