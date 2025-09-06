#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

void solve()
{
    int n,m;cin>>n>>m;
    vector<int>a(n+1),x(m+1),t(m+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    set<int>st[n+1];
    for(int i=1;i<=m;i++)
    {
        cin>>x[i]>>t[i];
        st[t[i]].insert(i);
    }
    priority_queue<pll,vector<pll>,greater<pll>>q;
    for(int i=1;i<=n;i++)
    {
        if(st[i].empty())
        {
            q.push({m+1,a[i]});
        }
        else
        {
            q.push({*st[i].begin(),a[i]});
        }
    }
    i64 ans=0;
    for(int i=1;i<=m;i++)
    {
        int len=x[i]-x[i-1];
        while(!q.empty())
        {
            auto [pri,val]=q.top();q.pop();
            if(len<val)
            {
                val-=len;
                ans+=len;
                len=0;
                q.push({pri,val});
                break;
            }
            else
            {
                len-=val;
                ans+=val;
            }
        }
        if(len)
        {
            cout<<ans<<"\n";
            return;
        }
        st[t[i]].erase(st[t[i]].begin());
        if(!(q.empty() || q.top().first>i))
        {
            q.pop();
        }
        if(st[t[i]].empty())
        {
            q.push({m+1,a[t[i]]});
        }
        else
        {
            q.push({*st[t[i]].begin(),a[t[i]]});
        }
    }
    while(!q.empty())
    {
        auto [pri,val]=q.top();q.pop();
        ans+=val;
    }
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}