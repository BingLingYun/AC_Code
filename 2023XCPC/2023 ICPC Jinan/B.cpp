#include<bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int,int> pii;

constexpr i64 mod=998244353;

void solve()
{
    int n,k;cin>>n>>k;
    vector<vector<int>>g(n+1);
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int sq = sqrt(n)*2;
    vector<int>siz(n+1);
    vector f(n+1,vector<int>(sq+10));
    vector<i64>dp(sq+10);
    unordered_map<int,int>F[n+1],G;

    function<void(int,int)> dfs1 = [&] (int u,int fa)
    {
        siz[u]=1;
        f[u][1]=1;
        for(auto v:g[u]) if(v!=fa)
        {
            dfs1(v,u);
            for(int j=0;j<=k+1;j++) dp[j]=0;
            for(int j=0;j<=min(k,siz[v]);j++)
            {
                for(int h=min(k+1-j,siz[u]);h>=1;h--)
                {
                    (dp[j+h]+=1ll*f[u][h]*f[v][j]%mod)%=mod;
                }
            }
            
            for(int j=0;j<=k+1;j++) f[u][j]=dp[j];
            siz[u]+=siz[v];
        }
        f[u][0]=(f[u][k]+f[u][k+1])%mod;
    };

    function<void(int,int)> dfs2 = [&] (int u,int fa)
    {
        siz[u]=1;
        F[u][1]=1;
        for(auto v:g[u]) if(v!=fa)
        {
            dfs2(v,u);
            G.clear();
            for(auto j:F[v])
            {
                for(auto h:F[u])
                {
                    if(j.first + h.first > k+1) continue;
                    (G[j.first+h.first] += 1ll * j.second*h.second%mod)%=mod;
                }
            }
            F[u].clear();
            for(auto j : G) F[u][j.first]=j.second;
            siz[u]+=siz[v];
        }
        F[u][0] = (F[u][k]+F[u][k+1])%mod;
        if(F[u][0]==0) F[u].erase(0);
        if(F[u][k]==0) F[u].erase(k);
        if(F[u][k+1]==0) F[u].erase(k+1);
        for(auto v:g[u]) if(v!=fa) F[v].clear();
    };

    if(k<=sq)
    {
        dfs1(1,0);
        cout<<f[1][0]<<"\n";
    }
    else
    {
        dfs2(1,0);
        cout<<F[1][0]<<"\n";
    }
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}