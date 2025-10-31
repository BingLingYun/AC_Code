#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

constexpr i64 mod = 998244353;

i64 fpow(i64 x, i64 y)
{
    i64 ans = 1;
    for (; y > 0; y >>= 1)
    {
        if (y & 1)
            ans = ans * x % mod;
        x = x * x % mod;
    }
    return ans;
}
void solve()
{
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
    vector<i64> fac(n + 1), tot(n + 1), son(n + 1), siz(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % mod;
    function<void(int, int)> dfs1 = [&](int u, int fa)
    {
        tot[u] = 1;
        son[u] = 0;
        siz[u] = 1;
        for (auto v : g[u])
        {
            if (v == fa)
                continue;
            dfs1(v, u);
            son[u]++;
            tot[u] *= tot[v];
            tot[u] %= mod;
            siz[u] += siz[v];
        }
        tot[u] *= fac[son[u]];
        tot[u] %= mod;
    };
    dfs1(1, 0);

    vector dp(n + 1, vector<i64>(n + 1));
    dp[1][1] = 1;
    function<void(int, int)> dfs2 = [&](int u, int fa)
    {
        vector f(son[u] + 1, vector<i64>(siz[u] + 1));
        f[0][0] = 1;
        for (auto v : g[u])
        {
            if (v == fa)
                continue;
            for (int i = son[u]; i >= 1; i--)
            {
                for (int j = siz[u]; j >= siz[v]; j--)
                {
                    f[i][j] = (f[i][j] + f[i - 1][j - siz[v]]) % mod;
                }
            }
        }
        i64 A = 1;
        for (auto v : g[u])
        {
            if (v == fa)
                continue;
            A = A * tot[v] % mod;
        }
        for (auto v : g[u])
        {
            if (v == fa)
                continue;
            for (int i = 1; i <= son[u]; i++)
            {
                for (int j = siz[v]; j <= siz[u]; j++)
                {
                    f[i][j] = (f[i][j] - f[i - 1][j - siz[v]] + mod) % mod;
                }
            }
            vector<i64> g(n + 2);

            for (int i = 0; i <= son[u] - 1; i++)
            {
                for (int k = 0; k <= siz[u]; k++)
                {
                    g[k + 1] += (fac[i] * fac[son[u] - 1 - i]) % mod * f[i][k];
                    g[k + 1] %= mod;
                }
            }
            i64 sum = A * fpow(tot[v], mod - 2) % mod;

            for (int i = 1; i <= n; i++)
            {
                for (int k = 1; k <= n; k++)
                {
                    if (i + k > n)
                        continue;
                    dp[v][i + k] += dp[u][i] * g[k] % mod * sum % mod;
                    dp[v][i + k] %= mod;
                }
            }

            for (int i = son[u]; i >= 1; i--)
            {
                for (int j = siz[u]; j >= siz[v]; j--)
                {
                    f[i][j] = (f[i][j] + f[i - 1][j - siz[v]]) % mod;
                }
            }
        }
        for (auto v : g[u])
        {
            if (v == fa)
                continue;
            dfs2(v, u);
        }
    };
    dfs2(1, 0);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            i64 res = dp[i][j] * tot[i] % mod;
            cout << res << " ";
        }
        cout << "\n";
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
    return 0;
}
// dp[u][x]表示节点u在DFS序中第x个位置，且只有以u为根节点的子树的顺序未确定的方案数
// ans[u][x]表示节点u在DFS序中第x个位置的方案数
// son[u]表示u的儿子的数量
// tot[u]表示以u为根节点的子树的DFS序的方案数