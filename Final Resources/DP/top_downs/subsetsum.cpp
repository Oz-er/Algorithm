#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


bool subsum(vector<int> &v,int i,int target){
    
    //base case
    if(target==0) return true;
    if(i==0 && target>0) return false;

    int num = v[i-1];

    //choice 1
    bool notTake = subsum(v,i-1,target);
    cout<<num<<" hey"<<endl;
  

    bool take=false;
    //choice 2 
    if(num<=target){
         take =subsum(v,i-1,target-num);
         cout<<num<<" gey"<<endl;
    }


    return take||notTake;





}



int main(){
    int target;

    cin>>target;

    vector<int>v={1,2,3,4,5,6,7,8,9};

    bool verdict;

    verdict=subsum(v,v.size(),target);


    if(verdict){
        cout<<"subset exists"<<endl;
    }

    else{
        cout<<"no subsets"<<endl;
    }


}