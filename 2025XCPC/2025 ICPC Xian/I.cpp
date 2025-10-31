#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

const i64 mod = 998244353;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(10);

    int n;cin>>n;
    vector a(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            cin>>a[i][j];
            a[j][i]=a[i][j];
        }
    }
    vector<vector<int>>e(n+1);
    vector<int>dep(n+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            int now = a[1][j] ^ a[1][i] ^ a[i][j];
            if(now == a[j][j])
            {
                e[j].push_back(i);
                dep[i]++;
            }
        }
    }
    vector<vector<int>>g(n+1);
    queue<int>q;q.push(1);
    while(!q.empty())
    {
        auto u=q.front();q.pop();
        for(auto v:e[u])
        {
            dep[v]--;
            if(!dep[v])
            {
                q.push(v);
                g[u].push_back(v);
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(auto j:g[i])
        {
            cout<<i<<" "<<j<<"\n";
        }
    }
    return 0;
}