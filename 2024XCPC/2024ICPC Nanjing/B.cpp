#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string s;
    cin >> s;

    int cnt2 = 0, cnt[2][2]{};
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '2')
        {
            cnt2++;
        }
        else
        {
            cnt[i & 1][s[i] - '0']++;
        }
    }

    int cnt1 = abs(cnt[0][1] - cnt[1][1]);
    int cnt0 = abs(cnt[0][0] - cnt[1][0]);

    int tmp = min(cnt0, cnt2);
    cnt2 -= tmp;
    cnt0 -= tmp;

    tmp = min(cnt1, cnt2);
    cnt2 -= tmp;
    cnt1 -= tmp;

    cnt2 %= 2;

    cout << (cnt0 + cnt1 + cnt2) << "\n";
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}