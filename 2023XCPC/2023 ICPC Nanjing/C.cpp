#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;
constexpr i64 mod=998244353;

void solve()
{
    i64 P,m;cin>>P>>m;
    i64 ans=0;
    i64 L=m/P-1,R=(m-2)/P+2;
    ans+=max(0LL,L+1);
    for(i64 i=L+1;i<=R;i++)
    {
        i64 now=P*i+1;
        i64 c=P-1;
        i64 h=now^c;
        if(h<=m) ans++;
    }
    cout<<ans<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(20);
    
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;    
}