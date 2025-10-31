#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int root = 0;
    for (int i = 1; i <= n; i++)
    {
        if (g[i].size() > g[root].size())
        {
            root = i;
        }
    }
    vector<array<int, 3>> ans;
    function<void(int, int)> dfs = [&](int u, int fa)
    {
        if (u != root)
        {
            for (auto v : g[u])
                if (v != fa)
                {
                    ans.push_back({root, u, v});
                }
        }
        for (auto v : g[u])
            if (v != fa)
            {
                dfs(v, u);
            }
    };
    dfs(root, 0);
    cout << ans.size() << "\n";
    for (auto [x, y, z] : ans)
        cout << x << " " << y << " " << z << "\n";
    return 0;
}