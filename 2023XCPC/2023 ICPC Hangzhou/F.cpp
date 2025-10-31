#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int, int> pii;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<pii> w(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i].first, w[i].second = i;
    vector<vector<pii>> g(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<i64> dis(n + 1);
    vector<int> dep(n + 1, 0), a(2 * n + 1), p(n + 1);
    int tim = 0;
    function<void(int, int)> dfs = [&](int u, int fa)
    {
        dep[u] = dep[fa] + 1;
        a[++tim] = u;
        p[u] = tim;
        for (auto [v, w] : g[u])
            if (v != fa)
            {
                dis[v] = dis[u] + w;
                dfs(v, u);
                a[++tim] = u;
            }
    };
    dfs(1, 0);

    vector<vector<pii>> f(tim + 1, vector<pii>(31));
    for (int i = 1; i <= tim; i++)
    {
        f[i][0] = {dep[a[i]], a[i]};
    }
    int len = (int)(log(tim) / log(2));
    for (int j = 1; j <= len; j++)
    {
        for (int i = 1; i <= tim - (1 << j) + 1; i++)
        {
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
    auto quiry = [&](int l, int r)
    {
        l = p[l], r = p[r];
        if (l > r)
            swap(l, r);
        int ln = (int)(log(r - l + 1) / log(2));
        return (min(f[l][ln], f[r - (1 << ln) + 1][ln]));
    };
    
    sort(w.begin()+1,w.end());

    vector<pii>pre(n+1);
    pre[1]={w[1].second,w[1].second};
    auto get_dis = [&] (int x,int y)
    {
        auto [_,lca]=quiry(x,y);
        i64 res = dis[x]+dis[y]-2ll*dis[lca];
        return res;
    };
    for(int i=2;i<=n;i++)
    {
        auto [x,y]=pre[i-1];
        int cc=w[i].second;
        i64 res1 = get_dis(x,cc);
        i64 res2 = get_dis(y,cc);
        i64 res3 = get_dis(x,y);
        if(res1>=res2 && res1>=res3) pre[i]={x,cc};
        else if(res2>=res1 && res2>=res3) pre[i]={y,cc};
        else pre[i]={x,y};
    }
    
    vector<int>mex(n+1);
    for(int i=1;i<=n;i++)
    {
        if(i==1)
        {
            if(w[i].first==0) mex[i]=1;
        }
        else
        {
            mex[i]=mex[i-1];
            if(w[i].first==mex[i]) mex[i]++;
        }
    }
    
    auto check = [&] (int pos,i64 x,i64 mx)
    {
        auto [u,v]=pre[pos];
        i64 res1 = get_dis(u,x);
        i64 res2 = get_dis(v,x);
        if(res1>mx || res2>mx) return false;
        else return true;
    };
    while(q--)
    {
        i64 x,k;cin>>x>>k;
        int l=1,r=n,res=-1;
        while(l<=r)
        {
            int mid=l+r>>1;
            if(check(mid,x,k)) res=mid,l=mid+1;
            else r=mid-1; 
        }
        if(res==-1) cout<<0<<"\n";
        else cout<<mex[res]<<"\n";
    }
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout << fixed << setprecision(15);

    int t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
    return 0;
}