#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        if (x != 0)
        {
            g[i].push_back(x);
            g[x].push_back(i);
        }
        if (y != 0)
        {
            g[i].push_back(y);
            g[y].push_back(i);
        }
    }
    vector<int> siz(n + 1), weight(n + 1), centroid(2), vis(n + 1);

    int tot = n;
    function<void(int, int)> GetCentroid = [&](int u, int fa)
    {
        siz[u] = 1;
        weight[u] = 0;
        for (auto v : g[u])
        {
            if (v == fa || vis[v])
                continue;
            GetCentroid(v, u);
            siz[u] += siz[v];
            weight[u] = max(weight[u], siz[v]);
        }
        weight[u] = max(weight[u], tot - siz[u]);
        if (weight[u] <= tot / 2)
        {
            centroid[centroid[0] != 0] = u;
        }
    };

    function<int(int, int)> dfs2 = [&](int u, int fa)
    {
        int cnt = 1;
        for (auto v : g[u])
            if (v != fa && !vis[v])
            {
                cnt += dfs2(v, u);
            }
        return cnt;
    };
    auto ask = [&](int u, int v)
    {
        cout << "? " << u << " " << v << endl;
        int res;
        cin >> res;
        return res;
    };

    int root = 1;
    while (1)
    {
        centroid[0] = centroid[1] = 0;
        tot = dfs2(root, 0);
        GetCentroid(root, 0);
        root = centroid[0];
        vector<int> now;
        for (auto x : g[root])
            if (!vis[x])
                now.push_back(x);

        if (now.size() == 0)
            break;
        if (now.size() == 3)
        {
            int u = now[0];
            int v = now[1];
            int z = now[2];
            if(siz[u]<siz[v]) swap(u,v);
            if(siz[v]<siz[z]) swap(v,z);
            int res = ask(u, v);
            if (res == 1)
            {
                vis[u] = vis[v] = 1;
            }
            else if (res == 0)
            {
                vis[root] = 1;
                root = u;
            }
            else
            {
                vis[root] = 1;
                root = v;
            }
        }
        else if (now.size() == 2)
        {
            int u = now[0];
            int v = now[1];
            int res = ask(u, v);
            if (res == 1)
            {
                break;
            }
            else if (res == 0)
            {
                vis[root] = 1;
                root = u;
            }
            else
            {
                vis[root] = 1;
                root = v;
            }
        }
        else if (now.size() == 1)
        {
            int u = now[0];
            int res = ask(u, root);
            if (res == 0)
            {
                vis[root]=1;
                root = u;
            }
            else
            {
                break;
            }
        }
    }
    cout << "! " << root << endl;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}