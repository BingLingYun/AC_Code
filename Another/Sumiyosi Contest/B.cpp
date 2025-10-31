#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

constexpr i64 mod = 998244353;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a.begin()+1,a.end());
    vector<i64>ans(n+1);
    vector suf(n+2,vector<i64>(m+2));
    auto dp = suf;
    suf[n+1][0]=1;
    for(int i=n;i>=1;i--)
    {
        suf[i]=suf[i+1];
        for(int k=m;k>=0;k--)
        {
            (suf[i][min(a[i]+k,m)]+=suf[i+1][k])%=mod;
        }
    }
    vector C(n+1,vector<int>(n+1));
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(i==j || j==0) C[i][j]=1;
            else
            {
                C[i][j] = (C[i-1][j-1]+C[i-1][j])%mod;
            }
        }
    }
    for(int i=n+1;i>=1;i--)
    {
        for(int k=m;k>=0;k--)
        {
            dp[i][k]=(dp[i][k+1]+suf[i][k])%mod;
        }
    }
    for(int k=0;k<=n;k++)
    {
        for(int i=k+1;i<=n;i++)
        {
            ans[k]+=1ll*C[i-1][k]*dp[i+1][max(m-a[i],0)]%mod;
            ans[k]%=mod;
        }
    }
    for(int k=0;k<=n;k++) cout<<ans[k]<<"\n";
    return 0;
}