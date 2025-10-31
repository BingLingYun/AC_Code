#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

void solve()
{
    int a,b,c;cin>>a>>b>>c;
    i64 now=1;
    i64 ans=1ll*c*b;
    i64 base=0;
    for(int i=1;i<=32;i++)
    {
        now*=2;
        base+=a;
        i64 cnt=(c+now-1)/now;
        ans=min(ans,1ll*cnt*b+base);
    }
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}