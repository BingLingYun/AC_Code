#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
#define ld long double
using namespace std;

constexpr i64 mod = 998244353;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int n,m;cin>>n>>m;
    vector<array<int,3>>line(m+1);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;cin>>u>>v>>w;
        line[i]={u,v,w};
    }
    sort(line.begin()+1,line.end(),[&](const auto x,const auto y){
        return x[2]<y[2];
    });
    map<i64,int>mp;
    vector<array<int,3>>edge;
    for(int i=1;i<=m;i++)
    {
        auto [u,v,w]=line[i];
        if(u>v) swap(u,v);
        i64 val=1ll*u*n+v;
        if(mp[val]) continue;
        edge.push_back({u,v,w});
        mp[val]=1;
    }
    m=edge.size();
    auto check = [&] (int x)
    {
        vector<vector<pii>>e(n+1);
        for(int i=0;i<m;i++)
        {
            auto [u,v,w]=edge[i];
            if(w>=x) break;
            e[u].push_back({v,w});
            e[v].push_back({u,w});
        }
        vector<int>col(n+1,-1);
        int flag=1;
        function<void(int)> dfs = [&] (int u)
        {
            for(auto [v,w]:e[u])
            {
                if(col[v]==-1)
                {
                    col[v]=col[u]^1;
                    dfs(v);
                }
                else
                {
                    if(col[v]==col[u])
                    {
                        flag=0;
                    }
                }
            }
        };
        for(int i=1;i<=n;i++)
        {
            if(col[i]==-1)
            {
                col[i]=0;
                dfs(i);
            }
        }
        if(!flag) return flag;
        for(int u=1;u<=n;u++)
        {
            if(e[u].size()<2) continue;
            auto [cv,cw]=e[u][0];
            auto [dv,dw]=e[u][1];
            int val=cw+dw;
            if(val<x)
            {
                flag=0;break;
            }
        }
        return flag;
    };
    int l=1,r=1e9,res=-1;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid)) res=mid,l=mid+1;
        else r=mid-1;
    }
    if(res==1e9) res=-1;
    cout<<res<<"\n";
    return 0;
}
/*
5 6
1 5 4
1 3 4
4 1 5
2 1 2
2 5 4
1 2 1

5 6
1 2 1
2 3 1
3 4 1
4 5 1
1 2 3
1 3 2

5 3
1 2 1
1 2 1
1 2 1

5 3
1 2 1
2 5 1
3 4 1
*/