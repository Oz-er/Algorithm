#include<bits/stdc++.h>
using namespace std;

const int INF = 5000; 



// int mat[7][7]={
//         {0,50,60,INF,INF,INF,INF},
//         {50,0,INF,120,90,INF,INF},
//         {60,INF,0,INF,INF,50,INF},
//         {INF,120,INF,0,INF,80,70},
//         {INF,90,INF,INF,0,INF,40},
//         {INF,INF,50,80,INF,0,140},
//         {INF,INF,INF,70,40,140,0}
//     };


vector<vector<int>> floydwarshall(vector<vector<int>> &graph){

    int s =graph.size();
    vector<vector<int>>dp(s,vector<int>(s));
    
    for(int i=0;i<s;i++){
        for(int j=0;j<s;j++){
            dp[i][j]=graph[i][j];
        }
    }

    for(int k=0;k<s;k++){
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                if(k!=i && k!=j){
                dp[i][j] = min(dp[i][j],max(dp[i][k],dp[k][j]));
                }
            }
        }
    }


    return dp;

}




int main(){

    int c,s,q;

    int cs =1;

    while(cin>>c>>s>>q){
        
        if(c==0 && s==0 && q==0)return 0;

        cout<<"case #"<<cs<<endl;
        cs++;
        vector<vector<int>>graph(c,vector<int>(c));
        
        
        for(int i=0;i<c;i++){
            for(int j=0;j<c;j++){
                if(i==j){
                    graph[i][j]=0;
                }
                else{
                    graph[i][j]=INF;
                }
            }
        }



        while(s--){
            int c1,c2,d;
            cin>>c1>>c2>>d;
            graph[c1-1][c2-1]=d;
            graph[c2-1][c1-1]=d;
        }

        vector<vector<int>>optimized_graph(c,vector<int>(c));
        optimized_graph = floydwarshall(graph);

        while(q--){
            int start,end;
            cin>>start>>end;

            int ans = optimized_graph[start-1][end-1];

            if(ans==5000)cout<<"no path"<<endl;
            else{
                cout<<ans<<endl;
            }
        }
    }
}