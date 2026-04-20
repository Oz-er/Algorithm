#include<bits/stdc++.h>
using namespace std;
typedef long long ll;




vector<ll> computelps(string &pattern){
    
    ll patternsize = pattern.size();
    vector<ll>lps(patternsize);

    ll len = 0;
    lps[0] = 0;

    ll i=1;

    while(i<patternsize){
    
        if(pattern[len]==pattern[i]){
        len++;
        lps[i]=len;
        i++;
        }

        else{
//---------------next best smaller prefix------------
            if(len!=0){
            len = lps[len-1];
            }
//---------------------------------------------------
            

//--------------restart from 0-----------------------
            else{
            lps[i]=0;
            i++;
            }
            }
//--------------------------------------------------    
        }

    return lps;


}


void kmpSearch(string &text, string &pattern){
    ll n = text.size();
    ll m = pattern.size();
    bool found = false;
 
    vector<ll> lps = computelps(pattern);
 
    cout<<"LPS array: ";
    for(ll i=0; i<m; i++) cout<<lps[i]<<" ";
    cout<<endl;
 
    ll i = 0;   // index for text
    ll j = 0;   // index for pattern
 
    while(i < n){
        if(text[i] == pattern[j]){
            i++;
            j++;
        }
        if(j == m){
            cout<<"Pattern found at index: "<<(i-j)<<endl;
            found = true;
            j = lps[j-1];   // don't reset to 0, use prefix function
        }
        else if(i < n && text[i] != pattern[j]){
            if(j != 0){
                j = lps[j-1];   // shift using prefix function
            }
            else{
                i++;
            }
        }
    }
    if(!found) cout<<"Pattern not found"<<endl;
}



int main(){
    string pattern;
    cin>>pattern;

    ll l = pattern.size();

    vector<ll>lps(l);

    lps = computelps(pattern);

}



/* =========================================
SAMPLE INPUT
(Text S and Pattern p on separate lines)
=========================================
bacbababababacaab
ababaca
=========================================
EXPECTED OUTPUT:
=========================================
LPS array: 0 0 1 2 3 0 1
Pattern found at index: 8
=========================================
NOTES:
- LPS[j] = length of longest proper prefix of pattern[0..j]
  that is also a suffix
  For "ababaca":
    j=0 -> 'a'       -> 0  (no proper prefix)
    j=1 -> 'ab'      -> 0  (no match)
    j=2 -> 'aba'     -> 1  ("a" is both prefix and suffix)
    j=3 -> 'abab'    -> 2  ("ab" matches)
    j=4 -> 'ababa'   -> 3  ("aba" matches)
    j=5 -> 'ababac'  -> 0  (no match)
    j=6 -> 'ababaca' -> 1  ("a" matches)
- On mismatch at j, jump to j = lps[j-1] instead of restarting at 0
  This avoids redundant comparisons
- YOUR BUG: computelps() was missing "return lps;" at the end
- Complexity: O(n+m) — O(m) to build LPS, O(n) to match
=========================================
*/