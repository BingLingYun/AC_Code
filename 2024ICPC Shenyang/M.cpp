#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long i64;

constexpr i64 INF = 1e17;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n);
    vector<vector<pii>> e(n);
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        if (b == 0)
            continue;

        int na = ((a % n) + n) % n;
        int nb = ((na + b) % n + n) % n;
        g[na].push_back(nb);
        e[na].push_back({nb, b});
    }

    vector<int> dfn(n), low(n), s(n), in_stack(n);
    int dfncnt = 0, tp = 0, sc = 0;
    vector<int> scc(n); // 结点 i 所在 SCC 的编号
    vector<int> sz(n);  // 强连通 i 的大小

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
    for (int i = 0; i < n; i++)
    {
        if (!dfn[i])
            tarjan(i);
    }

    vector<vector<int>> edge(n);
    vector<vector<int>> vec(sc);
    for (int i = 0; i < n; i++)
    {
        vec[scc[i] - 1].push_back(i);
    }
    vector<vector<int>> ng(sc);
    map<pii, int> mp;
    for (int i = 0; i < n; i++)
    {
        for (auto j : g[i])
        {
            int x = scc[i] - 1, y = scc[j] - 1;
            if (x == y || mp[{x, y}])
                continue;
            ng[y].push_back(x);
            mp[{x, y}] = 1;
        }
    }
    vector<i64> h(n, INF);
    auto check = [&](int id)
    {
        int u = vec[id][0];
        h[u] = 0;
        int flag = 1;
        function<void(int)> dfs = [&](int x)
        {
            for (auto [y, z] : e[x])
            {
                if (scc[y] != scc[x])
                    continue;
                if (h[y] != INF && h[y] != h[x] + z)
                {
                    flag = 0;
                }
                else if (h[y] == INF)
                {
                    h[y] = h[x] + z;
                    dfs(y);
                }
            }
        };
        dfs(u);
        return flag == 0;
    }; // 检查编号为id的强连通是否存在权值和非0环
    vector<int> vis(sc);
    for (int i = 0; i < sc; i++)
    {
        if (check(i))
            vis[i] = 1;
    }
    queue<int> Q;
    for (int i = 0; i < sc; i++)
        if (vis[i])
            Q.push(i);
    while (!Q.empty())
    {
        auto u = Q.front();
        Q.pop();
        for (auto v : ng[u])
        {
            if (!vis[v])
            {
                vis[v] = 1;
                Q.push(v);
            }
        }
    }
    while (q--)
    {
        int x;
        cin >> x;
        x = ((x % n) + n) % n;
        int id = scc[x] - 1;
        cout << (vis[id] ? "Yes" : "No") << "\n";
    }
    return 0;
}