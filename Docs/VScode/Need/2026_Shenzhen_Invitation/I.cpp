#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string s;
    cin >> s;
    int a = s[0] - '0', b = s[1] - '0';
    if (s[0] == '9' || s[1] == '9')
    {
        cout << "No" << "\n";
        return;
    }
    if (s[0] > s[1])
    {
        cout << "No" << "\n";
        return;
    }
    if (a == 0)
    {
        if (b <= 6)
        {
            cout << "Yes" << "\n";
            for (int i = 1; i <= 6; i++)
                cout << 0 << " ";
            for (int i = 0; i <= 6; i++)
            {
                if (b != i)
                    cout << i << " ";
            }
            cout << "\n";
        }
        else if (b == 7)
        {
            cout << "Yes" << "\n";
            cout << "0 6 8 1 2 3 1 2 3 4 5 0" << "\n";
        }
        else if (b == 8)
        {
            cout << "Yes" << "\n";
            cout << "0 6 7 1 2 3 1 2 3 4 5 0" << "\n";
        }
        return;
    }
    else if (a == 1 && b == 1)
    {
        cout << "Yes" << "\n";
        cout << "4 0 5 7 6 8 0 2 3 1 0 0" << "\n";
    }
    else if (a == 2 && b == 2)
    {
        cout << "Yes" << "\n";
        cout << "0 5 6 7 8 1 1 2 3 4 0 0" << "\n";
    }
    else if (a == 3 && b == 3)
    {
        cout << "Yes" << "\n";
        cout << "0 1 2 3 4 5 0 1 2 6 7 8" << "\n";
    }
    else
        cout << "No" << "\n";
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