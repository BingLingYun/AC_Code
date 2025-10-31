#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
void solve()
{
    int n,m,k;cin>>n>>m>>k;
    vector flag(n+1,vector<int>(m+1));
    priority_queue<array<int,3>>q;
    vector dis(n+1,vector<int>(m+1,1e9));
    for(int i=1;i<=k;i++)
    {
        int x,y;cin>>x>>y;
        flag[x][y]=k-i;
        if(i==1)
        {
            q.push({0,x,y});
            dis[x][y]=0;
        }
    }
    vector<string>s(n+1);
    for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
    vector vis(n+1,vector<int>(m+1));
    while(!q.empty())
    {
        auto [val,x,y]=q.top();q.pop();
        val=-val;
        if(vis[x][y]) continue;
        vis[x][y]=1;
        // cout<<val<<" "<<x<<" "<<y<<"\n";
        for(int i=0;i<4;i++)
        {
            int fx=x+dx[i],fy=y+dy[i];
            if(fx<=0 || fy<=0 || fx>n || fy>m) continue;
            if(vis[fx][fy] || s[fx][fy]=='#') continue;
            if(dis[fx][fy] > max(val+1,flag[fx][fy]+1))
            {
                dis[fx][fy]=max(val+1,flag[fx][fy]+1);
                q.push({-dis[fx][fy],fx,fy});
            }
        }
    }
    unsigned long long ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(dis[i][j]>=1e9) continue;
            // cout<<"@ "<<i<<" "<<j<<" "<<dis[i][j]<<"\n";
            ans=(ans+1ll*dis[i][j]*dis[i][j]);
        }
    }
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);
    cout<<fixed<<setprecision(15);

    int t=1;
    // cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}