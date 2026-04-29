#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


class Solution {
public:


    int dp[510][510];


    int editdistance(string s1,string s2,int a,int b){
       
        if(dp[a][b]!=-1){
            return dp[a][b];
        }
        if(a==0)return b;
        if(b==0)return a;


        if(s1[a-1]==s2[b-1]){
            return dp[a][b]=editdistance(s1,s2,a-1,b-1);
        }

        return dp[a][b]= 1 + min({editdistance(s1,s2,a,b-1),editdistance(s1,s2,a-1,b),editdistance(s1,s2,a-1,b-1)});
    }



    int minDistance(string word1, string word2) {

        memset(dp,-1,sizeof(dp));
        return editdistance(word1,word2,word1.size(),word2.size());
        
    }
};



int main(){
    Solution s;

    string s1;
    string s2;

    cin>>s1>>s2;

    cout<<s.minDistance(s1,s2)<<endl;
}