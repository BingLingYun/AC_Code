#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    string s = "";
    while (n >= 97)
    {
        s += 'a';
        n -= 97;
    }
    if (n != 0 && s.size() == 0)
    {
        cout << "No" << "\n";
        return;
    }
    for (int i = 0; i < s.size(); i++)
    {
        if (n > 25)
        {
            s[i] = 'z';
            n -= 25;
        }
        else
        {
            s[i] = (char)('a' + n);
            n = 0;
            break;
        }
    }
    if (n != 0)
    {
        cout << "No" << "\n";
    }
    else
    {
        cout << "Yes" << "\n";
        cout << s << "\n";
    }
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