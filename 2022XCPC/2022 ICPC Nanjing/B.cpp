#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
#define ld long double
#define debug(x) cout << "# " << x << "\n"
using namespace std;

constexpr i64 mod = 998244353;

void solve()
{
    int n,k;cin>>n>>k;
    vector<int>a(n+2);
    for(int i=1;i<=n;i++) cin>>a[i];
    string s;cin>>s;s="1"+s+"1";
    vector<i64>f(n+2),g(n+2);
    deque<pll>q;

    q.push_back({0,0});
    for(int i=1;i<=n+1;i++)
    {
        if(q.front().second+k < i) q.pop_front();
        i64 now = q.front().first+a[i];
        while(!q.empty() && (q.back().first>=now || s[i]=='1')) q.pop_back();
        q.push_back({now,i});
        f[i]=now;
    }
    q.clear();

    q.push_back({0,n+1});
    for(int i=n;i>=0;i--)
    {
        if(q.front().second-k>i) q.pop_front();
        i64 now = q.front().first+a[i];
        while(!q.empty() && (q.back().first>=now || s[i]=='1')) q.pop_back();
        q.push_back({now,i});
        g[i]=now;
    }
    q.clear();

    vector<i64>tmp(n+2);
    int Q;cin>>Q;
    while(Q--)
    {
        int p,v;cin>>p>>v;
        int l=max(0,p-k),r=min(n+1,p+k);
        for(int i=p;i<=r;i++) tmp[i]=f[i];
        q.push_back({f[l],l});
        for(int i=l+1;i<p;i++)
        {
            if(q.front().second+k < i) q.pop_front();
            i64 now = f[i];
            while(!q.empty() && (q.back().first>=now || s[i]=='1')) q.pop_back();
            q.push_back({now,i});
        }
        for(int i=p;i<=r;i++)
        {
            if(q.front().second+k < i) q.pop_front();
            i64 now = q.front().first+(i==p ? v : a[i]);
            while(!q.empty() && (q.back().first>=now || s[i]=='1')) q.pop_back();
            q.push_back({now,i});
            f[i]=now;
        }
        q.clear();

        i64 ans=1e18;
        for(int i=p;i<=r;i++)
        {
            ans=min(ans,f[i]+g[i]-a[i]);
        }
        cout<<ans<<"\n";
        for(int i=p;i<=r;i++) f[i]=tmp[i],tmp[i]=0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}