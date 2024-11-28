#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
#define all(x) x.begin(),x.end()
using namespace std;

constexpr i64 mod=998244353;

const int N=500005,M=1000005,INF=0x3f3f3f3f;
struct edge{
    int v,nxt,cap,cost;
}edges[M<<1];
int dis[N],cur[N],head[N],vis[N];
i64 ret=0;
int tot=1;
void addedge(int u,int v,int w,int c)
{
    edges[++tot]={v,head[u],w,c};
    head[u]=tot;

    edges[++tot]={u,head[v],0,-c};
    head[v]=tot;
}
bool spfa(int s,int t)
{
    for(int i=s;i<=t;i++) dis[i]=INF,cur[i]=head[i];
    queue<int>q;
    q.push(s);dis[s]=0,vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();vis[u]=0;
        for(int i=head[u];i;i=edges[i].nxt)
        {
            int v=edges[i].v;
            if(edges[i].cap && dis[v] > dis[u] + edges[i].cost)
            {
                dis[v] = dis[u] + edges[i].cost;
                if(!vis[v]) q.push(v),vis[v]=1;
            }
        }
    }
    return dis[t]!= INF;
}
int dfs(int u, int t,int flow)
{
    if (u == t) return flow;
    vis[u]=1;
    int ans=0;
    for (int &i = cur[u]; i && ans < flow ; i = edges[i].nxt)
    {
        int v = edges[i].v;
        if (!vis[v]  && edges[i].cap && dis[v] == dis[u] + edges[i].cost)
        {
            int x=dfs(v,t,min(edges[i].cap,flow-ans));
            if(x)
            {
                ret += x*edges[i].cost; edges[i].cap-=x;edges[i^1].cap+=x;ans+=x;
            }
        }
    }
    vis[u]=0;
    return ans;
}
int mcmf(int s,int t)
{
    int ans=0;
    while(spfa(s,t))
    {
        int x;
        while((x = dfs(s,t,INF))) ans+=x;
    }
    return ans;
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);

    int n;cin>>n;
	vector<int>a(n+1),cnt(n+1),fac;
	for(int i=1;i<=n;i++) cin>>a[i];
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j*j<=a[i];j++)
		{
			if(a[i]%j) continue;
			fac.push_back(j);
			fac.push_back(a[i]/j);
		}
		int x=a[i];
		for(int j=2;j*j<=x;j++)
		{
			while(x%j==0) cnt[i]+=1,x/=j;
		}
		if(x>1) cnt[i]+=1;
		ans+=cnt[i];
	}
	sort(all(fac));
	fac.erase(unique(all(fac)),fac.end());
	int m=fac.size();
	map<int,int>mp;
	vector<int>h(m+1);
	for(int i=0;i<m;i++)
	{
		mp[fac[i]]=i+1;
		int x=fac[i],now=0;
		for(int j=2;j*j<=x;j++)
		{
			while(x%j==0) now+=1,x/=j;
		}
		if(x>1) now+=1;
		h[i+1]=now;
	}
	int s=0,t=n+m+1;
	for(int i=1;i<=n;i++)
	{
		addedge(s,i,1,0);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j*j<=a[i];j++)
		{
			if(a[i]%j) continue;
			int id=mp[j];
			addedge(i,id+n,1,0);
			if(j*j!=a[i])
			{
				addedge(i,mp[a[i]/j]+n,1,0);
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		addedge(i+n,t,1,h[i]);
	}
	mcmf(s,t);
	cout<<ans-ret<<"\n";
    return 0; 
}