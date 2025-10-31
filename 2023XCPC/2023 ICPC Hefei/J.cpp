#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(10);
    
    int n,m;cin>>n>>m;
    vector<vector<pii>>g(n+1);
    i64 ans=1e15;
    vector<array<int,3>>edge(m+1);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;cin>>u>>v>>w;
        if(u>v) swap(u,v);
        g[u].push_back({v,w});
        g[v].push_back({u,w});
        if(u==1 && v==n) ans=min(ans,1ll*w);
        edge[i]={u,v,w};
    }
    auto bfs = [&] (int x)
    {
        priority_queue<pii>q;
        vector<int>d(n+1,-1);
        q.push({0,x});
        while(!q.empty())
        {
            auto [val,u]=q.top();q.pop();
            val=-val;
            if(d[u]!=-1) continue;
            d[u]=val;
            for(auto [v,w]:g[u])
            {
                if(d[v]!=-1) continue;
                int now=max(val,w);
                q.push({-now,v});
            }
        }
        return d;
    };
    auto d1=bfs(1);
    auto dn=bfs(n);
    for(int i=1;i<=m;i++)
    {
        auto [u,v,w]=edge[i];
        int lx=d1[u],rx=dn[v];
        if(w>=lx && w>=rx)
        {
            ans=min(ans,1ll*w+max(lx,rx));
        }
        lx=d1[v],rx=dn[u];
        if(w>=lx && w>=rx)
        {
            ans=min(ans,1ll*w+max(lx,rx));
        }
    }
    cout<<ans<<"\n";
    return 0;
}