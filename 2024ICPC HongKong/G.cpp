#include <bits/stdc++.h>
#define endl '\n'
#define int long long
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;
const int M = 5e5 + 10;
vector<int> fac[M];
void init()
{
    for (int i = 1; i < M; i++)
    {
        for (int j = i; j < M; j += i)
        {
            fac[j].push_back(i);
        }
    }
}
const int N = 2e6 + 10;
int tr[N][26];
int sz[N];
int f[N];
int ans = 0;
int cnt = 0;
int n;
void insert(string s, int i)
{
    int p = 0;
    for (auto c : s)
    {
        int e = c - 'a';
        if (!tr[p][e])
        {
            tr[p][e] = ++cnt;
        }
        p = tr[p][e];
        sz[p]++;
        for (auto x : fac[sz[p]])
        {
            ans ^= (f[x] * x);
            f[x]++;
            ans ^= (f[x] * x);
        }
    }
}

void solve()
{
    cin >> n;
    for (int i = 0; i <= n; i++)
    {
        f[i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        insert(s, i);
        cout << ans << " ";
    }
    cout << endl;
    for (int i = 0; i <= cnt + 10; i++)
    {
        for (int j = 0; j < 26; j++)

        {
            tr[i][j] = tr[i][j] = 0;
            sz[i] = 0;
        }
    }

    ans = 0;
    cnt = 0;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    t = 1;
    cin >> t;
    init();
    while (t--)
    {
        solve();
    }
}