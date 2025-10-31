#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int M = 1e5;
int dp[2][M + 10], pre[M + 10], suf[M + 10];
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n;
    cin >> n;
    vector<int> D(n);
    for (int i = 1; i < n; i++)
        cin >> D[i];

    for (int i = 0; i <= M; i++)
        dp[0][i] = i, dp[1][i] = 1e9;

    auto modify = [&](int op)
    {
        pre[0] = dp[op][0];
        for (int i = 1; i <= M; i++)
        {
            pre[i] = min(pre[i - 1], dp[op][i] - i);
        }

        suf[M] = dp[op][M];
        for (int i = M - 1; i >= 0; i--)
        {
            suf[i] = min(suf[i + 1], dp[op][i]);
        }
    };
    modify(0);

    int lst = 0;

    for (int i = 2; i <= n; i++)
    {
        int op = lst ^ 1;
        for (int h = 0; h <= M; h++)
        {
            if (h + D[i - 1] <= M)
                dp[op][h] = min(dp[op][h], suf[h + D[i - 1]]);
            if (h >= D[i - 1])
                dp[op][h] = min(dp[op][h], pre[h - D[i - 1]] + h);
        }
        for (int h = 0; h <= M; h++)
            dp[lst][h] = 1e9;
        lst ^= 1;
        modify(lst);
    }
    int ans = 1e9;
    for (int i = M; i >= 0; i--)
        ans = min(ans, dp[lst][i]);
    cout << ans << "\n";
    return 0;
}