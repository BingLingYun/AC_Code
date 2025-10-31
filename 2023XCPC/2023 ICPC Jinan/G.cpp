#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=1e9+7;


void solve()
{
    int n,m;cin>>n>>m;
    vector<string>s(n+1);
    for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
    vector<vector<pii>>g(n+1);
    for(int j=1;j<=(m+1)/2;j++)
    {
        vector<int>vec;
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            int flag=0;
            if(s[i][j]=='1') cnt++,flag=1;
            if(j!=m-j+1 && s[i][m-j+1]=='1') cnt++,flag=1;
            if(flag) vec.push_back(i);
        }
        if(j!=m-j+1)
        {
            if(cnt>=3)
            {
                cout<<0<<"\n";
                return;
            }
        }
        else
        {
            if(cnt>=2) 
            {
                cout<<0<<"\n";
                return;
            }
        }
        if(vec.size()==2)
        {
            int x=vec[0],y=vec[1];
            if(s[x][j]==s[y][j])
            {
                g[x].push_back({y,1});
                g[y].push_back({x,1});
            }
            else
            {
                g[x].push_back({y,0});
                g[y].push_back({x,0});
            }
        }
    }
    i64 ans=1;
    vector<i64>fac(n+1);fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*2%mod;
    vector<int>vis(n+1,-1);
    i64 res=1;
    function<void(int,int)>dfs = [&] (int u,int fa)
    {
        for(auto [v,w]:g[u]) if(v!=fa)
        {
            if(vis[v]!=-1)
            {
                int nx=vis[u]^w;
                if(nx!=vis[v]) res=0;
            }
            else
            {
                int nx=vis[u]^w;
                vis[v]=nx;
                dfs(v,u);
            }
        }
    };
    for(int i=1;i<=n;i++) 
    {
        if(vis[i]!=-1) continue;
        if(g[i].empty())
        {
            ans=ans*2%mod;
            continue;
        }
        res=1;vis[i]=0;
        dfs(i,0);
        ans=ans*res*2%mod;
    }
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

