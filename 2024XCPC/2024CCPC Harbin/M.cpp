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
    int n;cin>>n;
    i64 ans=1;
    vector<int>vec;
    for(int i=1;i*i<=n;i++)
    {
        if(n%i) continue;
        vec.push_back(i);
        if(i*i!=n) vec.push_back(n/i);
    }
    sort(vec.begin(),vec.end());
    for(int i=1;i<vec.size();i++)
    {
        int x=vec[i-1],y=vec[i];
        int len=y-x;
        ans+=1ll*len*(n/x);
    }
    cout<<ans<<'\n';
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