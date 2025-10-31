#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long i64;

struct BIT
{
    vector<int> a;
    int n;
    BIT() {}
    BIT(int n)
    {
        this->n = n;
        init(n);
    }
    void init(int n)
    {
        a.resize(n + 1, 0);
    }
    void add(int x, int v)
    {
        for (int i = x; i <= n; i += (i & (-i)))
            a[i] += v;
    }
    int ask(int x)
    {
        int res = 0;
        for (int i = x; i > 0; i -= (i & (-i)))
            res += a[i];
        return res;
    }
    int ask(int l, int r)
    {
        return ask(r) - ask(l - 1);
    }
};
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector f(n + 1, vector<int>(31));
    vector<int> dep(n + 1), in(n + 1), out(n + 1), siz(n + 1);
    int dfn = 0;
    function<void(int, int)> dfs = [&](int u, int fa)
    {
        in[u] = ++dfn;
        f[u][0] = fa;
        dep[u] = dep[fa] + 1;
        siz[u] = 1;
        for (int i = 1; i <= 30; i++)
        {
            f[u][i] = f[f[u][i - 1]][i - 1];
        }
        for (auto v : g[u])
            if (v != fa)
            {
                dfs(v, u);
                siz[u] += siz[v];
            }
        out[u] = dfn;
    };
    dfs(1, 0);
    auto LCA = [&](int x, int y)
    {
        if (dep[x] > dep[y])
            swap(x, y);
        int temp = dep[y] - dep[x];
        for (int j = 0; temp; j++, temp >>= 1)
        {
            if (temp & 1)
                y = f[y][j];
        }
        if (y == x)
            return x;

        for (int i = 30; i >= 0 && x != y; i--)
        {
            if (f[x][i] != f[y][i])
            {
                x = f[x][i], y = f[y][i];
            }
        }
        return f[x][0];
    };

    vector<int> vis(n + 1);
    BIT bit(n);

    while (q--)
    {
        int k;
        cin >> k;
        vector<int> vec(k);
        for (int i = 0; i < k; i++)
        {
            cin >> vec[i];
            vis[vec[i]]++;
        }

        int flag = 1;

        for (int i = 0; i < k; i++)
        {
            if (vis[vec[i]] > 1)
            {
                flag = 0;
                break;
            }
        }
        if (vis[1] && vec[0] != 1)
        {
            flag = 0;
        }
        if (!flag)
        {
            cout << "No" << "\n";
            for (int i = 0; i < k; i++)
                vis[vec[i]] = 0;
            continue;
        }
        for (int i = 0; i < k; i++)
            vis[vec[i]] = 0;
        vector<int> rcv;
        rcv.push_back(vec[0]);
        vis[vec[0]] = 1;
        bit.add(in[vec[0]], 1);

        for (int i = 1; i < k; i++)
        {
            int nxt = vec[i], lst = vec[i - 1];
            if (bit.ask(in[nxt], out[nxt]) != 0)
            {
                flag = 0;
                break;
            }

            if (f[nxt][0] == lst)
            {
                rcv.push_back(nxt);
                vis[nxt] = 1;
                bit.add(in[nxt], 1);
                continue;
            }

            int lca = LCA(lst, nxt);
            if (f[nxt][0] != lca)
            {
                flag = 0;
                break;
            }
            int x = lst;
            while (x != lca)
            {
                if (!vis[x])
                {
                    break;
                }
                int cnt = bit.ask(in[x], out[x]);
                if (cnt != siz[x])
                {
                    flag = 0;
                    break;
                }
                x = f[x][0];
            }
            rcv.push_back(nxt);
            vis[nxt] = 1;
            bit.add(in[nxt], 1);
        }

        cout << (flag ? "Yes" : "No") << "\n";
        for (auto x : rcv)
        {
            vis[x] = 0;
            bit.add(in[x], -1);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}