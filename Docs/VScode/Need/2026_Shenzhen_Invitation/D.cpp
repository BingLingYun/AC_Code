#include <bits/stdc++.h>

using namespace std;

#define i64 long long

struct BIT
{
    vector<i64> a;
    int n;
    BIT(int n)
    {
        this->n = n;
        a.resize(n + 2, 0);
    }
    void add(int x, i64 v)
    {
        for (int i = x; i <= n; i += (i & (-i)))
        {
            a[i] += v;
        }
    }
    i64 ask(int x)
    {
        i64 res = 0;
        for (int i = x; i > 0; i -= (i & (-i)))
        {
            res += a[i];
        }
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> a(n + 1);
    vector<int> uni, nxt(n + 1), id(n + 1);
    for (int i = 1; i <= n; i++)
    {
        char ch;
        cin >> ch;
        if (ch == 'F')
        {
            int x;
            cin >> x;
            a[i] = {0, x};
            uni.push_back(x);
        }
        else
        {
            a[i] = {1, 0};
        }
    }

    sort(uni.begin(), uni.end());
    uni.erase(unique(uni.begin(), uni.end()), uni.end());
    int m = uni.size();
    for (int i = 1; i <= n; i++)
    {
        if (!a[i].first)
        {
            int fid = lower_bound(uni.begin(), uni.end(), a[i].second) - uni.begin() + 1;
            id[i] = m - fid + 1;
        }
    }
    reverse(uni.begin(), uni.end());

    int tmp = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i].first == 1)
        {
            if (tmp != 0)
                nxt[tmp] = i;
            tmp = i;
        }
    }
    if (tmp)
        nxt[tmp] = n + 1;

    BIT cnt(n);
    BIT sum(n);
    auto check = [&](int x)
    {
        int l = 1, r = m, res = -1;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (cnt.ask(mid) >= x)
                res = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        if (res == -1)
            return 0ll;
        i64 he = sum.ask(res);
        he -= 1ll * (cnt.ask(res) - x) * uni[res - 1];
        return he;
    };
    i64 ans = 0;
    int work = 0, fc = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!a[i].first)
        {
            cnt.add(id[i], 1);
            sum.add(id[i], a[i].second);
            fc++;
        }
        else
        {
            work++;
            int st = nxt[i];
            int L = st - i;
            vector<i64> now;
            for (int j = i + 1; j < st; j++)
            {
                now.push_back(1ll * a[j].second * (st - j));
            }
            sort(now.begin(), now.end(), [&](const auto x, const auto y)
                 { return x > y; });
            i64 now_sum = 0, res = 0;
            res = 1ll * L * check(min(work, fc));
            for (int j = 0; j < now.size(); j++)
            {
                if (j + 1 > work)
                {
                    break;
                }
                now_sum += now[j];
                int yu = work - j - 1;
                if (yu <= fc)
                {
                    res = max(res, now_sum + 1ll * L * check(yu));
                }
                else
                {
                    res = max(res, now_sum + 1ll * L * check(fc));
                }
            }
            // cout << res << "\n";
            ans += res;
        }
    }
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