#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    sort(a.begin() + 1, a.end(), [&](const auto x, const auto y)
         { return x[1] < y[1]; });
    vector<long double> dp(m + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= a[i][2]; j--)
        {
            dp[j] = max(dp[j], dp[j - a[i][2]] * (1.0 * (100 - a[i][0]) / 100) + (1.0 * a[i][0] / 100) * a[i][1]);
        }
    }
    long double ans = 0;
    for (int i = 0; i <= m; i++)
        ans = max(ans, dp[i]);
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout << fixed << setprecision(15);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}