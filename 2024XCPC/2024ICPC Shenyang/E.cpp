#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long i64;

constexpr i64 INF = 1e15;
constexpr int N = 16;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t;
    cin >> t;
    vector<i64> a(4);
    for (int i = 0; i < 4; i++)
        cin >> a[i];
    vector dis(N, vector<i64>(N, INF));
    vector<vector<int>> cost(4);
    cost[0] = {1, 2, 4, 8};
    cost[1] = {3, 12};
    cost[2] = {10, 5};
    cost[3] = {15};
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (auto x : cost[j])
            {
                int now = i ^ x;
                dis[i][now] = min(dis[i][now], 1ll * a[j]);
                dis[now][i] = min(dis[now][i], 1ll * a[j]);
            }
        }
    }
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    vector dp(1 << N, vector<i64>(N, INF));
    for (int i = 0; i < N; i++)
    {
        dp[1 << i][i] = dis[i][N - 1];
    }
    for (int i = 1; i < (1 << N); i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (dp[i][j] >= INF)
                continue;
            for (int k = 0; k < N; k++)
            {
                if (i >> k & 1)
                    continue;
                dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + dis[j][k]);
            }
        }
    }
    vector<i64> ans(1 << N, INF);
    for (int i = 1; i < (1 << N); i++)
    {
        for (int j = 0; j < N; j++)
        {
            ans[i] = min(ans[i], dp[i][j]);
        }
    }
    while (t--)
    {
        int n;
        cin >> n;
        int mask = 0;
        for (int i = 1; i <= n; i++)
        {
            int val = 0;
            string a1, a2;
            cin >> a1 >> a2;
            for (int j = 0; j < 2; j++)
            {
                val = val * 2 + (a1[j] - '0');
            }
            for (int j = 0; j < 2; j++)
            {
                val = val * 2 + (a2[j] - '0');
            }
            mask |= (1 << val);
        }
        i64 res = INF;
        for (int i = 1; i < (1 << N); i++)
        {
            int now = i & mask;
            if (now == mask)
            {
                res = min(res, ans[i]);
            }
        }
        cout << res << "\n";
    }
    return 0;
}