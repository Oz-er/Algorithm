#include<bits/stdc++.h>
using namespace std;
    



vector<int> trackback(vector<pair<int,int>>&v,
                vector<vector<int>>&dp,
                int cap){
    
    int row = dp.size()-1;
    int col = dp[0].size()-1;

    vector<int> taken_items;

    while(row>0 && col>0){
        if(dp[row][col]!=dp[row-1][col]){
            taken_items.push_back(row-1);
            col-=v[row-1].first;
        }
        row--;
    }

    return taken_items;
}


void knapsack(vector<pair<int,int>>&v, int cap,vector<vector<int>>&dp){

    int size=v.size();

    for (int i=0;i<=size;i++)dp[i][0] = 0;
    for (int j=0;j<=cap;j++)dp[0][j] = 0;


    for(int i =1;i<=size;i++){
        for(int j=1;j<=cap;j++){
            int weight = v[i-1].first;
            int price = v[i-1].second;

            if(weight<=j){
                dp[i][j]=max(dp[i-1][j],price+dp[i-1][j-weight]);
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }

}




int main(){



    int capacity;
    int n;
    cin>>capacity;
    cin>>n;
    
    vector<pair<int,int>> items(n);

    vector<vector<int>>dp(n+1,vector<int>(capacity+1));
    

    for(int i=0;i<n;i++){
        int weight;
        cin>>weight; 
        int price;
        cin>>price;

        items[i] ={weight,price};
    }

    knapsack(items,capacity,dp);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

    vector<int>taken_item;

    taken_item=trackback(items,dp,capacity);


    cout<<"max value : "<<dp[n][capacity]<<endl;

    cout<<"items taken :"<<endl;

    for(int i=0;i<taken_item.size();i++){
        cout<<taken_item[i]<<" ";
    }

    cout<<endl;
}