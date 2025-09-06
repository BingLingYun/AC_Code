#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

struct DSU{
	vector<int>fa,siz;
	DSU(int N){
		fa=vector<int>(N+1);
		iota(fa.begin(),fa.end(),0);
		siz=vector<int>(N+1,1);
	}
	int find(int x)
	{
		return (fa[x]==x ? x : fa[x]=find(fa[x]));
	}
	void unite(int x,int y)
	{
		x=find(x);y=find(y);
		if(x!=y)
		{
			if(siz[x]<siz[y]) swap(x,y);
			fa[y]=x;
			siz[x]+=siz[y];
			siz[y]=0;
		}
	}
	int getsiz(int x)
	{
		return siz[find(x)];
	}
};
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);
    
    int n,m,k;cin>>n>>m>>k;
    vector<int>vis(n+1);
    for(int i=1;i<=k;i++)
    {
        int x;cin>>x;
        vis[x]=1;
    }
    DSU dsu(n);
    vector<vector<int>>g(n+1);
    for(int i=1;i<=m;i++)
    {
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
        if(vis[u] || vis[v]) continue;
        dsu.unite(u,v);
    }
    int flag=0,root=0;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]) continue;
        int siz=dsu.getsiz(i);
        if(siz+k==n)
        {
            root=i;
            flag=1;break;
        }
    }
    if(!flag)
    {
        cout<<"No"<<"\n";
        return 0;
    }
    vector<int>used(n+1);
    vector<vector<int>>ans;
    used[root]=1;
    function<void(int,int)> dfs = [&](int u,int fa)
    {
        vector<int>now;
        now.push_back(u);
        int cnt=0;
        for(auto v:g[u]) if(v!=fa)
        {
            if(!used[v]) cnt++;
        }
        if(cnt)
        {
            now.push_back(cnt);
            for(auto v:g[u]) if(v!=fa)
            {
                if(!used[v]) now.push_back(v),used[v]=1;
            }
            ans.push_back(now);
            for(int i=2;i<now.size();i++)
            {
                if(vis[now[i]]) continue;
                dfs(now[i],u);
            }
        }
    };
    dfs(root,0);
    for(int i=1;i<=n;i++)
    {
        if(!used[i])
        {
            cout<<"No"<<"\n";
            return 0;
        }
    }
    cout<<"Yes"<<"\n";
    cout<<ans.size()<<"\n";
    for(auto v:ans)
    {
        for(auto x:v) cout<<x<<" ";
        cout<<"\n";
    }
    return 0; 
}