#include<bits/stdc++.h>
using namespace std;

const long long mod=1e9+7;

inline void solve()
{
    string s;
    cin >> s;
    map<char, int> cnt;
    for(auto c: s) {
        cnt[c] ++;
    }
    vector<pair<int, char>> a;
    for(int i=0; i<26; i++) {
        if(cnt[i+'a'] != 0)
            a.push_back({cnt[i+'a'], (char)(i+'a')});
    }
    sort(a.begin(), a.end(), [&](auto x, auto y){
        return x.first < y.first;
    });
    string res = "";
    while(1) {
        bool p = 0;
        for(auto &[x, y]: a) {
            if(x > 0) {
                res.push_back(y);
                x --;
                p = 1;
            }
        }
        if(!p) break;
    }
    string t=" "+res;
    int n=t.size()-1;
    vector<long long>pre(n+1),suf(n+2),fac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*131%mod;
    for(int i=1;i<=n;i++)
    {
        pre[i]=pre[i-1]*131%mod+(t[i]-'a'+1);
        pre[i]%=mod;
    }
    for(int i=n;i>=1;i--)
    {
        suf[i]=suf[i+1]*131%mod+(t[i]-'a'+1);
        suf[i]%=mod;
    }
    auto check = [&] (int l,int r)
    {
        long long res1 = (pre[r]-pre[l-1]*fac[r-l+1]%mod+mod)%mod;
        long long res2 = (suf[l]-suf[r+1]*fac[r-l+1]%mod+mod)%mod;
        return res1==res2;
    };
    // cout<<res<<"\n";
    int flag=1;
    for(int i=2;i<=n;i++)
    {
        if(check(1,i)) flag=0;
    }
    if(res.size() == 1 || flag) {
        cout << "YES" << endl;
        cout << res << endl;
    } else {
        cout<<"NO"<<"\n";
    }
}
int main()
{
    int t;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}