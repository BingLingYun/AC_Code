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
    int n,q;cin>>n>>q;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<vector<int>>vec(n+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j*j<=i;j++)
        {
            if(i%j) continue;
            vec[i].push_back(j);
            if(j*j!=i) vec[i].push_back(i/j); 
        }
    }
    vector<int>mp(n+1),h(n+1);
    int cnt=0;
    auto add = [&] (int x)
    {
        if(mp[x]>0)
        {
            h[mp[x]]--;
        }
        mp[x]++;
        h[mp[x]]++;
    };
    auto del = [&] (int x)
    {
        h[mp[x]]--;
        mp[x]--;
        if(mp[x]>0)
        {
            h[mp[x]]++;
        }
    };
    for(int i=1;i<n;i++)
    {
        if(a[i]<=a[i+1])
        {
            continue;
        }
        else
        {
            cnt++;
            for(auto val:vec[i]) add(val);
        }
    }
    if(cnt==0) cout<<n<<"\n";
    else cout<<h[cnt]<<"\n";
    for(int i=1;i<=q;i++)
    {
        int x,y;cin>>x>>y;
        if(x>1 && a[x]<a[x-1])
        {
            cnt--;
            for(auto val:vec[x-1]) del(val);
        }
        if(x<n && a[x]>a[x+1])
        {
            cnt--;
            for(auto val:vec[x]) del(val);
        }
        a[x]=y;
        if(x>1 && a[x]<a[x-1])
        {
            cnt++;
            for(auto val:vec[x-1]) add(val);
        }
        if(x<n && a[x]>a[x+1])
        {
            cnt++;
            for(auto val:vec[x]) add(val);
        }
        if(cnt==0) cout<<n<<"\n";
        else cout<<h[cnt]<<"\n";
    }
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