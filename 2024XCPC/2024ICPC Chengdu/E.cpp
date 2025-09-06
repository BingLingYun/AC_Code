#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
#define all(x) x.begin(),x.end()
using namespace std;

constexpr i64 mod=998244353;

void solve()
{
    int n,q;cin>>n>>q;
    vector<vector<int>>g(n+1);
    for(int i=2;i<=n;i++)
    {
        int x;cin>>x;
        g[x].push_back(i);
    }

    vector<vector<int>>fa(n+1,vector<int>(31,0));
    vector<int>dep(n+1,0);
    vector<i64>h(n+1);
    vector<vector<i64>>dp(n+1,vector<i64>(2));//0表示包含子树根节点的连通子图数量，1表示不一定包含子树根节点的连通子图数量
    vector<vector<i64>>ddp(n+1,vector<i64>(2));//0表示包含除子树根节点外包含父节点的连通子图数量，1表示除子树根节点外不一定包含父节点的连通子图数量
    function<void(int,int)> dfs1 = [&] (int u,int father)
    {
        fa[u][0]=father;dep[u]=dep[father]+1;
        dp[u][0]=1;
        for(int i=1;i<=30;i++)
        {
            fa[u][i]=fa[fa[u][i-1]][i-1];
        }
        for(int v:g[u])
        {
            dfs1(v,u);
            dp[u][0]=dp[u][0]*(dp[v][0]+1)%mod;
            dp[u][1]=(dp[u][1]+dp[v][1])%mod;
            h[u]=(h[u]+dp[v][1])%mod;
        }
        dp[u][1]=(dp[u][1]+dp[u][0])%mod;
    };
    auto LCA = [&](int x,int y)
    {
        if(dep[x]>dep[y]) swap(x,y);
        int temp=dep[y]-dep[x];
        for(int j=0;temp;j++,temp>>=1)
        {
            if(temp&1) y=fa[y][j];
        }
        if(y==x) return x;

        for(int i=30;i>=0 && x!=y ;i--)
        {
            if(fa[x][i]!=fa[y][i])
            {
                x=fa[x][i],y=fa[y][i];
            }
        }
        return fa[x][0];
    };
    function<void(int,int)> dfs2 = [&] (int u,int father)
    {
        vector<i64>pre,suf;
        for(auto v:g[u]) pre.push_back(dp[v][0]+1),suf.push_back(dp[v][0]+1);
        for(int i=1;i<pre.size();i++) pre[i]=pre[i-1]*pre[i]%mod;
        for(int i=suf.size()-2;i>=0;i--) suf[i]=suf[i+1]*suf[i]%mod;
        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i];
            ddp[v][0]=(ddp[u][0]+1)*(i>0 ? pre[i-1] : 1)%mod*(i<g[u].size()-1 ? suf[i+1] : 1)%mod;
            ddp[v][1]=(ddp[u][1]+h[u]-dp[v][1]+ddp[v][0]+mod)%mod;
        }
        for(auto v:g[u]) dfs2(v,u);
    };
    vector<i64>pre(n+1);
    function<void(int,int)> dfs3 = [&] (int u,int father)
    {
        pre[u]=pre[father]+dp[u][0];
        pre[u]%=mod;
        for(auto v:g[u])
        {
            dfs3(v,u);
        }
    };
    auto getpre = [&] (int u,int v,int lca)
    {
        i64 val=pre[u]+pre[v]-pre[lca]-pre[fa[lca][0]]+mod+mod;val%=mod;
        return val;
    };
    dfs1(1,0);
    dfs2(1,0);
    dfs3(1,0);
    while(q--)
    {
        int u,v;cin>>u>>v;
        int lca=LCA(u,v);
        i64 res=(dp[1][1]-(ddp[lca][1]+dp[lca][1]-getpre(u,v,lca)+mod)%mod +mod)%mod;
        cout<<res<<"\n";
    }
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