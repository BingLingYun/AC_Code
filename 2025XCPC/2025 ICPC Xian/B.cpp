#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
#define ld long double
#define debug(x) cout << "# " << x << "\n"
using namespace std;

constexpr i64 mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = " " + s + " ";
    auto num = [&](char ch)
    {
        if (ch == 'C')
            return 0;
        else if (ch == 'W')
            return 1;
        else if (ch == 'P')
            return 2;
        else
            return -1;
    };
    auto cha = [&](int dir)
    {
        if (dir == 0)
            return 'C';
        else if (dir == 1)
            return 'W';
        else if (dir == 2)
            return 'P';
        else
            return ' ';
    };
    vector pre(n + 1, vector<int>(3));
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1];
        pre[i][num(s[i])]++;
    }
    int lx = 0, rx = 0;
    for (int i = 1; i < n; i++)
    {
        if (s[i] == s[i + 1])
        {
            lx = i;
            break;
        }
    }
    for (int i = n - 1; i >= 1; i--)
    {
        if (s[i] == s[i + 1])
        {
            rx = i;
            break;
        }
    }
    if (lx == 0)
    {
        cout << "Beautiful" << "\n";
        return;
    }
    int A = max({pre[n][0], pre[n][1], pre[n][2]});
    if (2 * A > n + 1)
    {
        cout << "Impossible" << "\n";
        return;
    }
    auto get_OK = [&](vector<int> cnt, int lx, int rx)
    {
        int sum = cnt[0] + cnt[1] + cnt[2];
        int mx = max({cnt[0], cnt[1], cnt[2]});
        if (2 * mx > sum + 1)
            return false;
        if (2 * mx == sum + 1)
        {
            for (int i = 0; i < 3; i++)
            {
                if (cnt[i] == mx)
                {
                    if (i == lx || i == rx)
                        return false;
                }
            }
            return true;
        }
        else if (2 * mx == sum)
        {
            int flag = 0;
            for (int i = 0; i < 3; i++)
            {
                if (cnt[i] == mx)
                {
                    if (i == lx && i == rx)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        return true;
    };
    auto check = [&](int x)
    {
        for (int l = 1; l <= lx + 1; l++)
        {
            int r = l + x - 1;
            if (r < rx || r > n)
                continue;
            vector<int> cnt(3);
            for (int i = 0; i < 3; i++)
                cnt[i] = pre[r][i] - pre[l - 1][i];
            int xl = num(s[l - 1]), xr = num(s[r + 1]);
            int B = max({cnt[0], cnt[1], cnt[2]});
            if (2 * B > r - l + 2)
                continue;
            int flag = get_OK(cnt, xl, xr);
            if (flag)
                return make_pair(1, l);
        }
        return make_pair(0, 0);
    };

    int len = max(2, rx - lx);
    int l = len, r = n, res = -1;
    int ansl, ansr;
    while (l <= r)
    {
        int mid = l + r >> 1;
        auto [flag, sta] = check(mid);
        if (flag)
        {
            res = mid, r = mid - 1;
            ansl = sta, ansr = sta + mid - 1;
        }
        else
            l = mid + 1;
    }

    cout << "Possible" << "\n";
    cout << ansl << " " << ansr << "\n";
    string ans = " ";
    for (int i = 1; i < ansl; i++)
        ans += s[i];
    vector<int> cnt(3);
    for (int i = 0; i < 3; i++)
        cnt[i] = pre[ansr][i] - pre[ansl - 1][i];
    int xl = num(s[ansl - 1]), xr = num(s[ansr + 1]);
    for (int i = ansl; i <= ansr; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!cnt[j] || xl == j)
                continue;
            cnt[j]--;
            int flag = get_OK(cnt, j, xr);
            if (flag)
            {
                ans += cha(j);
                xl = j;
            }
            else
            {
                cnt[j]++;
            }
        }
    }
    for (int i = ansr + 1; i <= n; i++)
        ans += s[i];
    for (int i = 1; i <= n; i++)
        cout << ans[i];
    cout << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
//二分