#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;
void init()
{
}
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    vector<int> c(n + 1);
    vector<int> d(n + 1);
    int sumb = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        sumb += b[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> d[i];
    }
    vector<int> sumc(n + 1);
    vector<int> sumd(n + 1);
    for (int i = 1; i <= n; i++)
    {
        sumc[i] = sumc[i - 1] + c[i];
    }
    for (int i = 1; i <= n; i++)
    {
        sumd[i] = sumd[i - 1] + d[i];
    }
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i = 1; i <= n; i++)
    {
        heap.push(a[i] - b[i]);
    }
    int res = sumd[n] + sumb;
    int tot = res;
    for (int i = 1; i <= n; i++)
    {
        tot += heap.top();
        heap.pop();
        tot -= d[n - i + 1];
        tot += c[i];
        res = min(res, tot);
    }
    cout << res << endl;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    t = 1;
    //    cin>>t;
    init();
    while (t--)
    {
        solve();
    }
}