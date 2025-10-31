#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

const i64 mod = 998244353;

struct Point
{
    i64 x, y;
};

i64 cross(Point p0, Point p1, Point p2)
{
    i64 v1x = p1.x - p0.x;
    i64 v1y = p1.y - p0.y;
    i64 v2x = p2.x - p1.x;
    i64 v2y = p2.y - p1.y;
    return v1x * v2y - v1y * v2x;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(10);

    int n;
    cin >> n;

    vector<Point> p(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i].x >> p[i].y;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int prev = (i - 1 + n) % n;
        int next = (i + 1) % n;

        Point pre = p[prev];
        Point cur = p[i];
        Point nxt = p[next];

        if (cur.y < pre.y && cur.y < nxt.y)
        {
            if (cross(pre, cur, nxt) > 0)
            {
                ans++;
            }
        }
        else if (cur.y < pre.y && cur.y == nxt.y && nxt.x>cur.x)
        {
            int j = i;
            while (p[(j + 1 + n) % n].y == cur.y)
            {
                j = (j + 1 + n) % n;
                if (j == i)
                    break;
            }

            if (j == i)
                continue;

            int now = (j + 1 + n) % n;

            if (p[now].y > cur.y)
            {
                ans++;
            }
            if(j>i) i = j;
            else break;
        }
    }
    cout << ans << "\n";
    return 0;
}