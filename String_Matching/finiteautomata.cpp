#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//---------- delta[q][a] = longest prefix of P that is a suffix of Pq+a ----------
vector<vector<ll>> computeTransitionFunction(string &pattern, string &alphabet){
    ll m = pattern.size();
    ll alpha_size = alphabet.size();

    vector<vector<ll>> delta(m+1, vector<ll>(alpha_size, 0));

    for(ll q=0; q<=m; q++){
        for(ll a=0; a<alpha_size; a++){
            ll k = min(m, q+1);
            string pqa = pattern.substr(0, q) + alphabet[a];

            while(k > 0){
                if(pqa.size() >= (size_t)k && pqa.substr(pqa.size()-k) == pattern.substr(0, k)){
                    break;
                }
                k--;
            }
            delta[q][a] = k;
        }
    }
    return delta;
}

void finiteAutomatonSearch(string &text, string &pattern){
    ll n = text.size();
    ll m = pattern.size();

    //---------- build alphabet from all unique chars in text + pattern ----------
    string combined = text + pattern;
    sort(combined.begin(), combined.end());
    combined.erase(unique(combined.begin(), combined.end()), combined.end());
    string alphabet = combined;

    auto charIndex = [&](char c) -> ll {
        return find(alphabet.begin(), alphabet.end(), c) - alphabet.begin();
    };

    vector<vector<ll>> delta = computeTransitionFunction(pattern, alphabet);

    //---------- print transition table ----------
    cout<<"Transition table:"<<endl;
    cout<<"state\t";
    for(char c : alphabet) cout<<c<<"\t";
    cout<<endl;
    for(ll q=0; q<=m; q++){
        cout<<q<<"\t";
        for(ll a=0; a<(ll)alphabet.size(); a++) cout<<delta[q][a]<<"\t";
        cout<<endl;
    }
    cout<<endl;

    //---------- scan text: one state transition per character ----------
    ll q = 0;
    bool found = false;
    for(ll i=0; i<n; i++){
        q = delta[q][charIndex(text[i])];
        if(q == m){
            cout<<"Pattern found at index: "<<(i-m+1)<<endl;
            found = true;
        }
    }
    if(!found) cout<<"Pattern not found"<<endl;
}

int main(){
    string text, pattern;
    cin>>text>>pattern;
    finiteAutomatonSearch(text, pattern);
}

/* =========================================
SAMPLE INPUT
(Pattern = "abba", the FA in your slides accepts "abba")
=========================================
ababbaabba
abba
=========================================
EXPECTED OUTPUT:
=========================================
Transition table:
state   a   b
0       1   0
1       1   2
2       1   3
3       4   0
4       1   2

Pattern found at index: 2
Pattern found at index: 6
=========================================
NOTES:
- FA has m+1 = 5 states (0 to 4) for pattern "abba"
- State 4 is the accepting state (full match)
- The transition table matches your slides exactly
- State sequence for "ababbaabba":
  a->1, b->2, a->1, b->2, b->3, a->4* (match at index 2)
  a->1, b->2, b->3, a->4*             (match at index 6)
- Complexity: O(m^3 * |alphabet|) to build table, O(n) to match
=========================================
*/