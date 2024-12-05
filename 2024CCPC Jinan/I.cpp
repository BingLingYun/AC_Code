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
    int n;cin>>n;
    vector<vector<int>>g(n+1);
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int root=0;
    for(int i=1;i<=n;i++)
    {
        if(g[i].size() %2 ==0)
        {
            root=i;break;
        }
    }
    if(!root)
    {
        cout<<-1<<"\n";
        return;
    }
    vector<pii>ans;
    vector<int>val(n+1);iota(val.begin(),val.end(),0);
    function<void(int,int)>dfs = [&] (int u,int fa)
    {
        vector<int>vec;
        for(auto v:g[u]) if(v!=fa)
        {
            dfs(v,u);
            vec.push_back(v);
        }
        if(vec.size()%2==0)
        {
            for(int i=1;i<vec.size();i+=2)
            {
                ans.push_back({val[vec[i]],val[vec[i-1]]});
            }
        }
        else
        {
            for(int i=1;i<vec.size();i+=2)
            {
                ans.push_back({val[vec[i]],val[vec[i+1]]});
            }
            val[u]=val[vec[0]];
        }
    };
    dfs(root,0);
    cout<<ans.size()<<"\n";
    for(auto [x,y]:ans) cout<<x<<" "<<y<<"\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout<<fixed<<setprecision(15);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}