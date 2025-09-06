#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

void solve()
{
    int n, k, q;
    cin >> n >> k >> q;
    vector<vector<int>> g(n + 1);
    vector a(k + 1, vector<int>(n + 1));
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
        for (int j = 1; j < n; j++)
        {
            g[a[i][j]].push_back(a[i][j + 1]);
        }
    }
    vector<int> dfn(n + 1), low(n + 1), s(n + 1), in_stack(n + 1);
    int dfncnt = 0, tp = 0, sc = 0;
    vector<int> scc(n + 1); // 结点 i 所在 SCC 的编号
    vector<int> sz(n + 1);  // 强连通 i 的大小

    function<void(int)> tarjan = [&](int u)
    {
        low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
        for (auto v : g[u])
        {
            if (!dfn[v])
            {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (in_stack[v])
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u])
        {
            ++sc;
            while (s[tp] != u)
            {
                scc[s[tp]] = sc;
                sz[sc]++;
                in_stack[s[tp]] = 0;
                --tp;
            }
            scc[s[tp]] = sc;
            sz[sc]++;
            in_stack[s[tp]] = 0;
            --tp;
        }
    };
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            a[i][j]=scc[a[i][j]];
        }
    }
    vector pre(k+1,vector<i64>(n+1));
    vector L(k+1,vector<int>(n+1)),R(k+1,vector<int>(n+1));
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            int r=j;
            while(r<n && a[i][r+1] == a[i][r]) r++;
            for(int k=j;k<=r;k++) L[i][k]=j,R[i][k]=r;
            int len=r-j+1;
            pre[i][r]=pre[i][j-1]+1ll*len*(len-1)/2;
            j=r; 
        }
    }
    i64 ans=0;
    while(q--)
    {
        i64 id,l,r;cin>>id>>l>>r;
        id = (id+ans)%k+1;
        l = (l+ans)%n+1;
        r = (r+ans)%n+1;
        ans=0;
        if(a[id][l] == a[id][r])
        {
            int len = r-l+1;
            ans = 1ll*len*(len-1)/2;
        }
        else
        {
            int lx = R[id][l];
            ans+=1ll*(lx-l+1)*(lx-l)/2;
            int rx = L[id][r];
            ans+=1ll*(r-rx+1)*(r-rx)/2;
            if(lx+1!=rx)
            {
                rx--;
                ans+=pre[id][rx]-pre[id][lx];
            }
        }
        cout<<ans<<"\n";
    }
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}