#include<bits/stdc++.h>
using namespace std;

const int INF = 5000; 



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
                dp[i][j] = min(dp[i][j],dp[i][k]+dp[k][j]);
                }
            }
        }
    }


    return dp;

}




int main(){


    int u,v;
    int caseNum=1;

    while(cin>>u>>v && (u!=0 || v!=0)){


    int from,to;
    set<int>s;
    vector<pair<int,int>>edges;

    s.insert(u);
    s.insert(v);

    edges.push_back({u,v});


    while(cin>>from>>to){
        
        if(from==0 && to==0){
            break;
        }

        s.insert(from);
        s.insert(to);

        edges.push_back({from,to});
    }



    int sz=s.size();
    vector<vector<int>>graph(101,vector<int>(101));    


    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++){
            if(i==j)graph[i][j]=0;
            else graph[i][j]=INF;
        }
    }


    for(int i=0;i<edges.size();i++){
        graph[edges[i].first-1][edges[i].second-1]=1;
    }

    vector<vector<int>>graph2(101,vector<int>(101));

    graph2 = floydwarshall(graph);

    double clicks =0;

    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++){
            if(graph2[i][j]!=INF){
                clicks+=graph2[i][j];
            }
        }
    }


    double pairs = sz*(sz-1);


    double ans = clicks/pairs;

    cout <<"Case "<<caseNum<<": average length between pages = "<<fixed<<setprecision(3)<<ans<<" clicks" <<endl;
    caseNum++;
}
   
}