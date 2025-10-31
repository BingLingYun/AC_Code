#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;
constexpr i64 mod=998244353;

void solve()
{
    int a,b,c,d;cin>>a>>b>>c>>d;
    int ans=0;
    for(int i=a;i<=min(b,a+10);i++)
    {
        for(int j=c;j<=min(d,c+10);j++)
        {
            int x=i+j;
            while(x) ans=max(ans,x%10),x/=10;
        }
    }
    cout<<ans<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(10);
    
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;    
}