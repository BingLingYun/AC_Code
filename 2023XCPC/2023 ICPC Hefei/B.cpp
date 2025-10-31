#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

int dp[510][510];
int C[510][510];
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(10);
    
    int n;cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<int>sum(n+1);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    C[0][0]=1;
    for(int i=1;i<=sum[n];i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
        {
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
    dp[0][0]=1;
    for(int i=0;i<=n-1;i++)
    {
        for(int j=0;j<=sum[i];j++)
        {
            if(dp[i][j])
            {
                dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
                for(int k=j+1;k<=sum[i+1]-1;k++)
                {
                    int lb = max(0, a[i + 1] - (k - j)), ub = min(a[i + 1] - 1, sum[i + 1] - k - 1);
                    for(int x=lb;x<=ub;x++)
                    {
                        dp[i+1][k]=(dp[i+1][k]+1ll*dp[i][j]*C[k-j-1][a[i+1]-x-1]%mod)%mod;
                    }
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=sum[n];i++)
    {
        ans=(ans+dp[n][i])%mod;
    }
    cout<<ans<<"\n";
    return 0;
}