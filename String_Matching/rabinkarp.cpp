#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll q = 101;    // prime modulus so that 2q fits in one word
const ll base = 2;   // binary alphabet base

void rabinKarp(string &text, string &pattern){
    ll n = text.size();
    ll m = pattern.size();
    bool found = false;

    //---------- hash the pattern using Horner's rule ----------
    ll p_hash = 0;
    for(ll i=0; i<m; i++){
        p_hash = (base * p_hash + pattern[i]) % q;
    }

    //---------- hash the first window of the text ----------
    ll t_hash = 0;
    for(ll i=0; i<m; i++){
        t_hash = (base * t_hash + text[i]) % q;
    }

    //---------- offset = base^(m-1) % q, used in rolling hash ----------
    ll offset = 1;
    for(ll i=0; i<m-1; i++){
        offset = (base * offset) % q;
    }

    for(ll s=0; s<=n-m; s++){
        if(p_hash == t_hash){
            //---------- hash matched: verify char-by-char to rule out collisions ----------
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
        //---------- rolling update: drop leftmost char, add next char ----------
        if(s < n-m){
            t_hash = (base * (t_hash - offset * text[s] % q + q) + text[s+m]) % q;
        }
    }
    if(!found) cout<<"Pattern not found"<<endl;
}

int main(){
    string text, pattern;
    cin>>text>>pattern;
    rabinKarp(text, pattern);
}

/* =========================================
SAMPLE INPUT
(Text T and Pattern P on separate lines)
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
- Pattern hash computed once using Horner's rule: p = 2*p + P[i]
- Rolling hash formula: t[s] = (2*(t[s-1] - offset*T[s-1]) + T[s+m-1]) % q
  This updates the window in O(1) instead of recomputing from scratch
- When hashes match, still verify char-by-char to handle hash collisions
- Average complexity: O(n+m), worst case (all collisions): O(n*m)
=========================================
*/