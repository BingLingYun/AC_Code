#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;
constexpr i64 mod=998244353;

void solve()
{
    int n,m;cin>>n>>m;
    vector<vector<int>>vec(m+1);
    for(int i=1;i<=n;i++)
    {
        int p;cin>>p;
        for(int j=1;j<=p;j++)
        {
            int x;cin>>x;
            vec[x].push_back(i);
        }
    }
    vector<int>deg(n+1);
    vector<vector<int>>g(n+1);
    for(int i=1;i<=m;i++)
    {
        if(vec[i].size()<=1) continue;
        for(int j=0;j<vec[i].size()-1;j++)
        {
            int x=vec[i][j],y=vec[i].back();
            g[x].push_back(y);
            deg[y]++;
        }
    }
    priority_queue<int>q;
    for(int i=1;i<=n;i++) if(!deg[i]) q.push(i);
    vector<int>ans;
    while(!q.empty())
    {
        auto u=q.top();q.pop();
        ans.push_back(u);
        for(auto v:g[u])
        {
            deg[v]--;
            if(!deg[v]) q.push(v);
        }
    }
    for(int i=0;i<n;i++)
    {
        if(ans[i]!=i+1)
        {
            cout<<"Yes"<<"\n";
            for(auto x:ans) cout<<x<<" ";cout<<"\n";
            return;
        }
    }
    cout<<"No"<<"\n";
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