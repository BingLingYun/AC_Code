#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int n,m;cin>>n>>m;
    vector<i64>a(n+1),b(m+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];
    sort(a.begin()+1,a.end());
    sort(b.begin()+1,b.end());
    vector dp(n+1,vector<i64>(m+1,1e18));
    for(int i=0;i<=n;i++) dp[i][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=min(m,i);j++)
        {
            dp[i][j]=min(dp[i-1][j],dp[i][j]);
            dp[i][j]=min(dp[i][j],dp[i-1][j-1]+abs(a[i]-b[j]));
        }
    }
    cout<<dp[n][m]<<"\n";
    return 0;
}