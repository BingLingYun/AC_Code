#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;
constexpr i64 mod=998244353;

int dx[]={-1,1,0,0};
int dy[]={0,0,1,-1};

constexpr i64 base1=131;
constexpr i64 base2=1e9+7;

void solve()
{
    int n,m;cin>>n>>m;
    vector<string>s(n+1);
    for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
    vector<vector<int>>vis(n+1,vector<int>(m+1));

    int tot=0,cnt=0;
    set<pii>st[n*m+1];
    function<void(int,int)> dfs = [&] (int x,int y)
    {
        vis[x][y]=tot;st[tot].insert({x,y});
        for(int k=0;k<4;k++)
        {
            int fx=x+dx[k],fy=y+dy[k];
            if(fx<=0 || fy<=0 || fx>n || fy>m || vis[fx][fy] || s[fx][fy]!='.') continue;
            dfs(fx,fy);
        }
    };
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!vis[i][j] && s[i][j]=='.')
            {
                tot++;dfs(i,j);
            }
        }
    }

    auto check = [&] (int a,int b)
    {
        if(st[a].size()>st[b].size()) return 0;

        auto [x,y]=*st[a].begin();
        for(auto [nx,ny]:st[b])
        {
            int flag=1;
            int fx=nx-x,fy=ny-y;
            for(auto [nowx,nowy]:st[a])
            {
                int cx=nowx+fx,cy=nowy+fy;
                if(!st[b].count({cx,cy}))
                {
                    flag=0;break;
                }
            }
            if(flag) return 1;
        }
        return 0;
    };
    int ans=0;
    for(int i=1;i<=tot;i++)
    {
        int flag=0;
        for(int j=1;j<=tot;j++)
        {
            if(i==j) continue;
            if (check(i,j))
            {
                flag=1;break;
            }
        }
        if(!flag) ans+=st[i].size();
    }
    cout<<ans<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(20);
    
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;    
}