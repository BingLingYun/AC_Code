#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int, int> pii;

const int N = 10000;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<pii> line(m + 1);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        line[i] = {x, y};
    }

    vector<int> f(2 * n + 1), e(2 * n + 1), siz(2 * n + 1);
    iota(f.begin(), f.end(), 0);
    fill(siz.begin(), siz.end(), 1);
    function<int(int)> find = [&](int x)
    {
        if (f[x] == x)
            return x;
        int y = f[x];
        f[x] = find(y);
        e[x] ^= e[y];
        return f[x];
    };

    vector<int>cnt(n+1);

    auto check = [&]()
    {
        int sum = 0;
        cnt.assign(n + 1, 0);
        for (int i = 1; i <= 2 * n; i++)
        {
            if (i != f[i])
                continue;
            int v = abs(siz[i]);
            if (v > n)
                return false;
            sum += v;
            cnt[v]++;
        }
        bitset<N + 1> b=1;
        for (int x = 1; x <= n; x++)
        {
            if (cnt[x] > 0)
            {
                int k = 1;
                while (k < cnt[x])
                {
                    b |= b << (k * x);
                    cnt[x] -= k;
                    k *= 2;
                }
                b |= b << (cnt[x] * x);
            }
        }
        return (bool)b[sum / 2];
    };
    for (int i = m; i >= 1; i--)
    {
        auto [u, v] = line[i];
        int fu = find(u), fv = find(v);
        if (fu == fv)
            continue;

        int t = e[u] ^ e[v] ^ 1;
        f[fv] = fu;
        e[fv] = t;
        siz[fu] += (t ? -1 : 1) * siz[fv];

        if (!check())
        {
            siz[fu] -= (t ? -1 : 1) * siz[fv];
            t ^= 1;
            e[fv] = t;
            siz[fu] += (t ? -1 : 1) * siz[fv];
        }
    }

    vector<bitset<N + 1>> dp{1};
    vector<int> ans(2 * n + 1);
    int sum = 0;
    for (int i = 1; i <= 2 * n; i++)
    {
        if (i != find(i))
        {
            continue;
        }
        int v = abs(siz[i]);
        sum += v;
        dp.push_back(dp.back() | dp.back() << v);
    }
    int u = sum / 2;
    for (int i = 2 * n, j = dp.size() - 1; i >= 1; i--)
    {
        if (i != find(i))
        {
            continue;
        }
        int v = abs(siz[i]);
        j--;
        int r = (siz[i] >= 0);
        if (dp[j][u])
        {
            r ^= 1;
        }
        else
        {
            u -= v;
        }
        ans[i] = r;
    }

    for (int i = 1; i <= 2 * n; i++)
    {
        ans[i] = ans[find(i)];
        ans[i] ^= e[i];
    }
    for (int i = 1; i <= 2 * n; i++)
    {
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}