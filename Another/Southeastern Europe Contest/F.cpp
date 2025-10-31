#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> a(n + 1);
    set<int> mn, mx;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        for (int j = 1; j <= x; j++)
        {
            int val;
            cin >> val;
            a[i].push_back(val);
        }
        sort(a[i].begin(), a[i].end());
        mn.insert(a[i].front());
        mx.insert(a[i].back());
    }
    auto checkL = [&](int l, int r)
    {
        auto it = mx.upper_bound(l);
        if (it == mx.end() || *it >= r)
            return true;
        else
            return false;
    };
    auto checkR = [&](int l, int r)
    {
        auto it = mn.upper_bound(l);
        if (it == mn.end() || *it >= r)
            return true;
        else
            return false;
    };
    vector<array<int, 3>> vec;
    for (int i = 1; i <= n; i++)
    {
        int l = a[i].front(), r = a[i].back();
        for (auto x : a[i])
        {
            if (checkL(l, x) && checkR(x, r))
            {
                vec.push_back({l, r, i});
                break;
            }
        }
    }
    sort(vec.begin(), vec.end(), [&](auto x, auto y)
         { return x[1] < y[1]; });
    // cout<<vec.size()<<"\n";
    vector<int> vis(n + 1);
    int lst = 0;
    if (!vec.empty())
    {
        vis[vec[0][2]] = 1;
        lst = vec[0][1];
    }
    for (int i = 1; i < vec.size(); i++)
    {
        auto [l, r, id] = vec[i];
        if (l < lst)
            continue;
        vis[id] = 1;
        lst = r;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += (vis[i] ? 1 : 2);
    cout << ans << "\n";
    return 0;
}