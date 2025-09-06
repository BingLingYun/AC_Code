#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

i64 fpow(i64 x,i64 y)
{
    i64 ans=1;
    for(;y>0;y>>=1)
    {
        if(y&1) ans=ans*x%mod;
        x=x*x%mod;
    }
    return ans;
}
void solve()
{
    int n;cin>>n;
    vector<vector<int>>g(n+1);
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<i64>siz(n+1,1);
    vector<i64>sum(n+1);
    i64 ans=0;
    function<void(int,int)> dfs = [&] (int u,int fa)
    {
        for(auto v:g[u]) if(v!=fa)
        {
            dfs(v,u);
            siz[u]+=siz[v];
            (sum[u]+=sum[v])%=mod;
        }
        (sum[u]+=siz[u]*siz[u]%mod)%=mod;
        (ans+=(siz[u]*siz[u]%mod*(n-siz[u])%mod*(n-siz[u])%mod))%=mod;
        i64 res=0;
        for(auto v:g[u]) if(v!=fa)
        {
            (ans+=2ll*(n-siz[v])*(n-siz[v])%mod*((sum[v]-siz[v]*siz[v]%mod+mod)%mod)%mod)%=mod;
            (ans+=2ll*res*sum[v]%mod)%=mod;
            (res+=sum[v])%=mod;
        }
    };
    dfs(1,0);
    // cout<<ans<<"\n";
    i64 base=(1ll*n*(n-1)/2)%mod;
    base=1ll*base*base%mod;
    ans=ans*fpow(base,mod-2)%mod;
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}