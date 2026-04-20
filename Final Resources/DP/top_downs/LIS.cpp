#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


class Solution {
public:

    int dp[501][501];

    int lis(vector<int>&v1,vector<int>&v2,int a,int b){

        if(dp[a][b]!=-1){
            return dp[a][b];
        }

        if(a==0 || b==0){
            return 0;
        }

        if(v1[a-1]==v2[b-1]){
            return dp[a][b]=1+lis(v1,v2,a-1,b-1);
        }

        return dp[a][b]=max(lis(v1,v2,a-1,b),lis(v1,v2,a,b-1));
    }


    int lengthOfLIS(vector<int>& nums) {

        memset(dp,-1,sizeof(dp));
        vector<int>s;
        s=nums;

        sort(s.begin(),s.end());

        set<int>st;

        for(int i=0;i<s.size();i++){
            st.insert(s[i]);
        }

         vector<int>num2;

         for(int element : st){
            num2.push_back(element);
         }


        return lis(nums,num2,nums.size(),num2.size());
    }
};



int main(){

    Solution sol;

    vector<int>nums={10,9,8,1,2,3,5,6};

    cout<<sol.lengthOfLIS(nums)<<endl;

}