#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

void solve()
{
    int n;cin>>n;
    vector<vector<int>>g(n+1);
    vector<int>deg(n+1);
    for(int i=2;i<=n;i++)
    {
        int x;cin>>x;
        g[i].push_back(x);
        deg[x]++;
    }
    int ans=n;
    int res=0;
    queue<int>q;
    for(int i=1;i<=n;i++)
    {
        if(!deg[i]) q.push(i);
    }
    ans=min(ans,(int)q.size());
    while(!q.empty())
    {
        vector<int>vec;
        while(!q.empty()) vec.push_back(q.front()),q.pop();
        res+=1;
        for(auto u:vec)
        {
            for(auto v:g[u])
            {
                deg[v]--;
                if(!deg[v]) q.push(v);
            }
        }
        ans=min(ans,res+(int)q.size());
    }
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}