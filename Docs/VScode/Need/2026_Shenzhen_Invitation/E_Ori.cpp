#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    s = " " + s, t = " " + t;
    int A;
    cin >> A;
    int cnt = 0;
    for (int i = 1; i < A; i++)
    {
        if (s[i] == '1')
            cnt++;
    }
    if (cnt <= 1)
    {
        cout << "Yes" << "\n";
        return;
    }
    int tot = 0;
    for (int i = 1; i < A; i++)
    {
        if (t[i] == '1')
            tot++;
    }
    if (tot <= 1)
    {
        int r1 = n + 2, r2 = 0;
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == '2')
            {
                r1 = i;
                break;
            }
        }
        for (int i = n; i >= 1; i--)
        {
            if (t[i] == '2')
            {
                r2 = i;
                break;
            }
        }
        if (r1 < r2)
        {
            cout << "Yes" << "\n";
            return;
        }
        int R = r2;
        r1 = n + 2, r2 = 0;
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == '1')
            {
                r1 = i;
                break;
            }
        }
        for (int i = n; i >= 1; i--)
        {
            if (t[i] == '1')
            {
                r2 = i;
                break;
            }
        }
        if (r1 < r2 && r2 >= A)
        {
            cout << "Yes" << "\n";
            return;
        }
        if (!R && r1 < r2)
        {
            cout << "Yes" << "\n";
            return;
        }
    }
    int k = 0;
    for (int i = 1, j = 1; i <= n; i++)
    {
        if (t[i] == '2')
        {
            while (j < n && (j <= i || s[j] != '2'))
                j++;
            if (j > i && s[j] == '2')
            {
                k++;
                j++;
            }
        }
    }
    deque<int> a, b, c;
    for (int i = 1; i < A; i++)
    {
        if (s[i] == '1')
            a.push_back(i);
    }
    for (int i = A; i <= n; i++)
    {
        if (s[i] == '1')
            c.push_back(i);
    }
    for (int i = A; i <= n; i++)
    {
        if (t[i] == '1')
            b.push_back(i);
    }
    int X = a.size(), Y = b.size();
    int kk = 0;
    for (int i = 0; i < min(a.size(), b.size()); i++)
    {
        int x = b[i];
        while (!c.empty() && c.front() <= x)
        {
            c.pop_front();
        }
        if (!c.empty())
        {
            kk++;
            c.pop_front();
        }
        else
            break;
    }
    int H = min(k + kk, Y);
    if (X <= H + 1)
    {
        cout << "Yes" << "\n";
    }
    else
        cout << "No" << "\n";
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
/*
A的单数最多只有一个小等C的
如果B最多只有1个比C小等的单数，考虑是否能从A转到B先手，如果能转到或者让B最后打出就是Yes
*/