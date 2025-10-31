#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;
const int N = 110;
int fac[N];
int invfac[N];
int f[N][N][5050];
const int mod = 998244353;
int qmi(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
void init()
{
    fac[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fac[i] = (fac[i - 1] * i) % mod;
    }
    invfac[N - 1] = qmi(fac[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; i--)
    {
        invfac[i] = (invfac[i + 1] * (i + 1)) % mod;
    }
}
int C(int a, int b)
{
    if (a < 0 || b < 0 || a - b < 0)
    {
        return 0;
    }
    return fac[a] * invfac[b] % mod * invfac[a - b] % mod;
}
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % 2 == 1)
    {
        cout << 0 << endl;
        return;
    }
    sum /= 2;
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k <= sum; k++)
            {
                f[i][j][k] = f[i - 1][j][k] % mod;
                if (k - a[i] >= 0 && j - 1 >= 0)
                {
                    f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k - a[i]] * j % mod) % mod;
                }
            }
        }
    }
    int res = 0;
    for (int i = 1; i < n; i++)
    {
        // cerr << f[n][i][sum] << " " << i << endl;
        res = (res + f[n][i][sum] * fac[n - i] % mod) % mod;
    }
    cout << res << endl;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    t = 1;
    // cin>>t;
    init();
    while (t--)
    {
        solve();
    }
}