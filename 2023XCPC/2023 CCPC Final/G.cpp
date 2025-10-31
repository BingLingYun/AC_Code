#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long i64;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 2), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    sort(b.begin() + 1, b.end());
    for (int i = 1; i <= n; i++)
    {
        b[i] += b[i - 1];
    }
    priority_queue<i64>Q;
    a[n + 1] = m;
    i64 ans = 0;
    for (int i = n, j = n; i >= 0, j >= 1; i--)
    {
        while (j && b[j] > a[i + 1])
            j--;
        if (j == 0)
            break;
        if (b[j] < a[i])
        {
            Q.push(a[i+1]-a[i]);
            continue;
        }
        int l = j;
        while (l - 1 && b[l - 1] >= a[i])
            l--;
        
        for (int cc = l + 1; cc <= j; cc++)
        {
            if (Q.empty())
                break;
            i64 now = Q.top();Q.pop();
            ans+=now;
        }

        if (Q.empty())
        {
            ans += a[i + 1] - b[l];
            Q.push(b[l] - a[i]);
        }
        else
        {
            i64 res = a[i + 1] - b[l];
            i64 line = Q.top();Q.pop();
            if(res>line)
            {
                line += b[l]-a[i];
                ans+=res;Q.push(line);
            }
            else
            {
                ans+=line;
                Q.push(a[i+1]-a[i]);
            }
        }
        j=l-1;
    }
    cout<<ans<<"\n";
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
}