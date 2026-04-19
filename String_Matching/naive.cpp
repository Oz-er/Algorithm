#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void naiveSearch(string &text, string &pattern){
    ll n = text.size();
    ll m = pattern.size();
    bool found = false;

    for(ll s=0; s<=n-m; s++){
        bool match = true;
        for(ll i=0; i<m; i++){
            if(text[s+i] != pattern[i]){
            match = false;
            break;
            }
        }
        if(match){
        cout<<"Pattern found at index: "<<s<<endl;
        found = true;
        }
    }
    if(!found) cout<<"Pattern not found"<<endl;
}

int main(){
    string text, pattern;
    cin>>text>>pattern;
    naiveSearch(text, pattern);
}

/* =========================================
SAMPLE INPUT
(Based on slide 2: T = 000010001010001, P = 0001)
=========================================
000010001010001
0001
=========================================
EXPECTED OUTPUT:
=========================================
Pattern found at index: 1
Pattern found at index: 5
Pattern found at index: 11
=========================================
NOTES:
- Naive algorithm slides the pattern one by one over text
- At s=0: T[0..3] = "0000" != "0001" (mismatch at T[3])
- At s=1: T[1..4] = "0001" == "0001" -> MATCH
- At s=5: T[5..8] = "0001" == "0001" -> MATCH
- At s=11: T[11..14] = "0001" == "0001" -> MATCH
- Worst-case complexity: O(n*m)
=========================================
*/