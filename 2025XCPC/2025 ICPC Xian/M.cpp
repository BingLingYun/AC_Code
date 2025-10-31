#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

const i64 mod = 1e9+7;

i64 fpow(i64 x,i64 y)
{
    i64 ans=1;
    for(;y>0;y>>=1)
    {
        if(y&1) ans=ans*x%mod;
        x=x*x%mod;
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(10);

    int n,m;cin>>n>>m;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==-1) cnt++;
    }
    i64 ans=fpow(m,cnt);
    vector dp(n+1,vector<i64>(2));
    int flag=1;
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=1 && a[i]!=-1)
        {
            flag=0;break;
        }
    }
    if(flag && n>1 && n%2==1) flag=1;
    else flag=0;
    i64 res=0;
    if(m>=n)
    {
        dp[1][0]=0;
        if(a[1]==-1) dp[1][1]=m-n+1;
        else if(a[1]>=n) dp[1][1]=1;
        else dp[1][1]=0;

        for(int i=2;i<=n;i++)
        {
            if(a[i]==1 || a[i]==-1)
            {
                dp[i][0]=dp[i-1][1];
            }
            else
            {
                dp[i][0]=0;
            }

            i64 now=0;
            if(a[i]==-1) now = m-n+1;
            else if(a[i]>=n) now=1;

            if(now)
            {
                dp[i][1]=(dp[i-1][0]+dp[i-1][1])%mod*now%mod;
            }
            else dp[i][1]=0;
        }
        res = dp[n][1];
    }
    i64 sum = (ans-res+mod-flag+mod)%mod;
    cout<<sum<<"\n";
    return 0;
}
//成段的1 或者 首尾有1 或者至少一个 2 - n-1 的值