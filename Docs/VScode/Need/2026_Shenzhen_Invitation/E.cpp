#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    s = " " + s;
    t = " " + t;
    int pc;
    cin >> pc;
    vector<int> As, Al, PA;
    vector<int> Bs, Bl, PB;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == '1')
        {
            if (i < pc)
                As.push_back(i);
            else
                Al.push_back(i);
        }
        else if (s[i] == '2')
        {
            PA.push_back(i);
        }

        if (t[i] == '1')
        {
            if (i < pc)
                Bs.push_back(i);
            else
                Bl.push_back(i);
        }
        else if (t[i] == '2')
        {
            PB.push_back(i);
        }
    }
    auto get_match = [&](const vector<int> &X, const vector<int> &Y)
    {
        int i = 0, j = 0;
        int res = 0;
        while (i < X.size() && j < Y.size())
        {
            if (X[i] < Y[j])
            {
                res++;
                i++;
                j++;
            }
            else
            {
                j++;
            }
        }
        return res;
    };
    int SA = As.size(), LA = Al.size(), SB = Bs.size(), LB = Bl.size();
    if (SA <= 1)
    {
        cout << "Yes" << "\n";
        return;
    }
    if (SB <= 1)
    {
        if (SB == 1 && LB == 0 && PB.empty())
        {
            if (As[0] < Bs[0])
            {
                cout << "Yes" << "\n";
                return;
            }
        }
        else
        {
            if (LB >= 1 || get_match(Al, Bl) > 0 || get_match(PA, PB) > 0)
            {
                cout << "Yes" << "\n";
                return;
            }
        }
    }
    int req = SA - 1;
    if (LB >= req)
    {
        int x1 = get_match(Bl, Al);
        int x2 = get_match(PB, PA);
        if (x1 + x2 >= req)
        {
            cout << "Yes" << "\n";
            return;
        }
    }
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