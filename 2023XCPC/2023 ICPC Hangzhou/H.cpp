#include<bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int,int> pii;

constexpr i64 mod = 1e9+7;

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
    vector<i64>a(n+1),b(n+1),w(n+1);
    vector<vector<int>>g(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++) cin>>w[i];
    vector<int>vis(n+1);
    for(int i=1;i<=n;i++)
    {
        int nxt=b[i];
        g[nxt].push_back(i);
        if(a[i]<a[nxt]) vis[i]=1;
        else if(a[i]>=a[nxt]+w[nxt]) vis[i]=2;
        else vis[i]=3;
    }
    vector<i64>ans(n+1);
    for(int i=1;i<=n;i++) ans[i]=a[i];
    vector<i64>fac(n+1),inv(n+1);fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    inv[n]=fpow(fac[n],mod-2);
    for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;

    function<void(int,int)> dfs = [&] (int u,int dep)
    {
        ans[u]=(ans[u] + inv[dep]*w[u])%mod;
        for(auto v:g[u])
        {
            if(vis[v]==3) dfs(v,dep+1);
        }
    };
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==1) dfs(i,1);
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";cout<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);
    cout<<fixed<<setprecision(15);

    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}