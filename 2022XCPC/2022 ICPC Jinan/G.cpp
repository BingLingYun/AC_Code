#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 5e5;
int a[N + 10];

struct Info
{
    i64 mx, mn;
};
Info operator+(Info a, Info b)
{
    Info c;
    c.mn = min(a.mn, b.mn);
    c.mx = max(a.mx, b.mx);
    return c;
}
struct SegmentTree
{
    vector<Info> info;
    SegmentTree(int n)
    {
        init(n);
    }
    void init(int n)
    {
        info.resize(n << 2);
    }
    void pushup(int u)
    {
        info[u] = info[u << 1] + info[u << 1 | 1];
    }
    void build(int u, int l, int r) // 建树
    {
        if (l == r)
        {
            info[u].mn = info[u].mx = a[l];
            return;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void modify(int u, int l, int r, int pos, i64 k) // 当前区间与目的区间
    {
        if (pos == l && pos == r)
        {
            info[u].mn = info[u].mx = k;
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid)
            modify(u << 1, l, mid, pos, k);
        if (pos > mid)
            modify(u << 1 | 1, mid + 1, r, pos, k);
        pushup(u);
    }
    int quiry_left(int u, int l, int r, int x, int y, int aid)
    {
        if (info[u].mx < aid)
            return 0;
        if (l == r)
            return l;

        int mid = l + r >> 1;
        if (x <= l && r <= y)
        {
            int res = quiry_left(u << 1, l, mid, x, y, aid);
            if (res)
                return res;
            return quiry_left(u << 1 | 1, mid + 1, r, x, y, aid);
        }
        if (x <= mid)
        {
            int res = quiry_left(u << 1, l, mid, x, y, aid);
            if (res)
                return res;
        }
        return quiry_left(u << 1 | 1, mid + 1, r, x, y, aid);
    }

    int quiry_right(int u, int l, int r, int x, int y, int aid)
    {
        if (info[u].mn > aid)
            return 0;
        if (l == r)
            return l;

        int mid = l + r >> 1;
        if (x <= l && r <= y)
        {
            int res = quiry_right(u << 1 | 1, mid + 1, r, x, y, aid);
            if (res)
                return res;
            return quiry_right(u << 1, l, mid, x, y, aid);
        }
        if (mid + 1 <= y)
        {
            int res = quiry_right(u << 1 | 1, mid + 1, r, x, y, aid);
            if (res)
                return res;
        }
        return quiry_right(u << 1, l, mid, x, y, aid);
    }
};

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SegmentTree segment(n);
    segment.build(1, 1, n);
    int ans = 0;
    auto partition = [&](int l, int r)
    {
        int mid = l + r >> 1, aid = a[mid];
        int i = l - 1, j = r + 1;
        while (1)
        {
            i = segment.quiry_left(1, 1, n, i + 1, n, aid);
            j = segment.quiry_right(1, 1, n, 1, j - 1, aid);
            if (i >= j)
                return j;
            segment.modify(1, 1, n, i, a[j]);
            segment.modify(1, 1, n, j, a[i]);
            swap(a[i], a[j]);
            ans++;
        }
    };
    function<void(int, int)> qsort = [&](int l, int r)
    {
        if (l < 0 || r < 0 || l >= r)
            return;
        int p = partition(l, r);
        qsort(l, p);
        qsort(p + 1, r);
    };
    qsort(1, n);
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}