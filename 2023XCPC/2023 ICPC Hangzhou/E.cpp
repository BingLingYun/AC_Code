#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

struct lis
{
    int id;
    vector<int> ch;
    lis() { ch.resize(26, 0); }
};
bool operator < (const lis &A, const lis &B) {
    return A.id < B.id;
}
void solve()
{
    int n;
    cin >> n;
    vector<int> len(n + 1);
    vector<lis> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        len[i] = s.size();
        for (int j = 0; j < s.size(); j++)
        {
            a[i].ch[s[j] - 'a']++;
        }
        a[i].id=i;
    }
    set<pair<int, lis>> st;
    for (int i = n; i >= 1; i--)
    {
        while (st.size() && prev(st.end())->first >= len[i])
        {
            auto it = prev(st.end());
            int L = it->first;
            lis k = it->second;
            st.erase(it);
            int cnt = L / len[i];
            L %= len[i];
            for (int j = 0; j < 26; j++)
            {
                if (k.ch[j] < cnt * a[i].ch[j])
                {
                    cout << "NO" << "\n";
                    return;
                }
                k.ch[j] -= cnt*a[i].ch[j];
            }
            if(L) st.insert({L,k});
        }
        st.insert({len[i],a[i]});
    }
    string s1="";
    lis cur;
    for(auto [_,k]:st)
    {
        for(int j=0;j<26;j++)
        {
            if(k.ch[j] >= cur.ch[j])
            {
                for(int i=cur.ch[j]+1;i<=k.ch[j];i++)
                {
                    s1+=(char)(j+'a');
                }
                cur.ch[j]=k.ch[j];
            }
            else
            {
                cout<<"NO"<<"\n";
                return;
            }
        }
    }
    cout<<"YES"<<"\n";
    cout<<s1<<"\n";
    for(int i=2;i<=n;i++)
    {
        if(len[i]<s1.size()) s1.resize(len[i]);
        else
        {
            int d=s1.size();
            for(int j=d;j<len[i];j++)
            {
                s1+=s1[j%d];
            }
        }
        cout<<s1<<"\n";
    }
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout << fixed << setprecision(15);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}