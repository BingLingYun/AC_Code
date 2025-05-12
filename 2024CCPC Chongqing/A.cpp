#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
#define ld long double
using namespace std;

constexpr i64 mod = 998244353;

int q[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

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
i64 inv(int n)
{
    return fpow(n, mod - 2);
}
// f[i][S]表示从前i个数里面选若干个数的乘积的质因子集合为S的乘积之和
// f[i][S] -> f[i+1][S]
// f[i][S]*a[i+1] -> f[i+1][S U P(a[i]) ]

//值域为3000，53*61 > 3000 ,所以质因子大于等于53的最多包含一个
//相同最大质因子的排列在一起进行DP，专门考虑前15个质因子即可
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i], b[i] = a[i];
        for (int j = 0; j <= 14; j++)
        {
            while (b[i] % q[j] == 0)
            {
                b[i] /= q[j];
                c[i] |= 1 << j;
            }
        }
        if (b[i] % 53 == 0)
            b[i] = 53;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (b[i] > b[j])
            {
                swap(b[i], b[j]);
                swap(a[i], a[j]);
                swap(c[i], c[j]);
            }
        }
    }
    int mx = (1 << 15);
    vector<int> f(mx), g(mx);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        i64 e = inv(b[i]);
        for (int S = mx - 1; S >= 0; S--)
        {
            g[S | c[i]] = (g[S | c[i]] + 1ll * (f[S] + g[S]) * a[i]) % mod;
        }
        if (b[i] != b[i + 1])
        {
            for (int S = 0; S < mx; S++)
            {
                f[S] = (f[S] + (b[i] - 1 ? (b[i] - 1ll) * e % mod : 1) * g[S]) % mod;
                g[S] = 0;
            }
        }
    }
    i64 ans = 0;
    for (int S = 0; S < mx; S++)
    {
        for (int i = 0; i <= 14; i++)
        {
            if (S >> i & 1)
                f[S] = f[S] * (q[i] - 1ll) % mod * inv(q[i]) % mod;
        }
        ans = (ans + f[S]) % mod;
    }
    cout << ans << "\n";
    return 0;
}
/*
3
1 2 3
*/
