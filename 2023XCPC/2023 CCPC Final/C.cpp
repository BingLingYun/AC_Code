#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

void solve()
{
    int n,m;cin>>n>>m;
    vector<vector<int>>g(n+1);
    for(int i=1;i<=m;i++)
    {
        int u,v;cin>>u>>v;
        u++,v++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    g[1].push_back(n);
    for(int i=1;i<=n;i++)
    {
        sort(g[i].begin(),g[i].end());
    }
    vector<int>col(n+1,-1);
    for(int i=1;i<=n;i++)
    {
        if(i==1) col[i]=0;
        else 
        {
            if(col[i]==-1) col[i]=col[i-1]^1;
        }

        for(auto j:g[i])
        {
            if(col[j]==-1)
            {
                col[j]=col[i]^1;
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<(col[i] ? "B":"R");
    }
    cout<<"\n";
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t=1;
    cin >> t;
    while (t--)
    {
        solve();
    }
}