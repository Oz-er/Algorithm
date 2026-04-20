#include <bits/stdc++.h>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

#define ll long long
string s = "";

ll lcs(vector<string> s1, vector<string> s2)
{

    ll n = s1.size();
    ll m = s2.size();
    ll arr[n + 1][m + 1] = {0};
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {

            if (s1[i - 1] == s2[j - 1])
            {
                arr[i][j] = arr[i - 1][j - 1] + 1;
            }
            else
            {
                arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
            }
        }
    }
    ll i = n;
    ll j = m;
    while (i > 0 && j > 0)
    {

        if (s1[i - 1] == s2[j - 1])
        {
            {
            }
            s = s1[i - 1]+" "+s; 
            i--;
            j--;
        }
        else if (arr[i - 1][j] > arr[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    return arr[n][m];
}

void solve()
{
    vector<string> files;

    for (auto &entry : fs::directory_iterator("."))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
        {
            string filename = entry.path().filename().string();
            if (filename != "hello.txt")
            {
                files.push_back(filename);
            }
        }
    }

    for (auto &file2 : files)
    {
        s = "";
        ifstream f1("hello.txt");
        ifstream f2(file2);
        string line1;
        string line2;
        string s1;
        string s2;

        while (getline(f1, line1))
        {
            s1 += line1;
            if (!f1.eof())
                s1 += '\n';
        }
        while (getline(f2, line2))
        {
            s2 += line2;
            if (!f2.eof())
                s2 += '\n';
        }
        vector<string> v1, v2;
        stringstream a(s1);
        stringstream b(s2);
        string word;
        while (a >> word)
        {
            if (!(ispunct(word[0])) && !ispunct(word[word.size() - 1]))
            {
                v1.push_back(word); 
            }
        }
        while (b >> word)
        {
            if (!(ispunct(word[0])) && !ispunct(word[word.size() - 1]))
            {
                v2.push_back(word); 
            }
        }
        cout << " vs " << file2 << ":" << endl;
        ll ans = lcs(v1, v2);
        cout << ans << endl;
        double percentage = (double)(ans / (double)((max(s1.size(), s2.size()))));
        cout << percentage * 100 << endl;
        cout << s << endl;
        cout << endl;
        f1.close();
        f2.close();
    }
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    while (t--)
    {
        solve();
    }
}