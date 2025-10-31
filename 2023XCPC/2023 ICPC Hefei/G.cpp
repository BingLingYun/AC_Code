#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(10);
    
    int n,m,k;cin>>n>>m>>k;
    string s;cin>>s;s=" "+s;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) a[i]=s[i]-'0';

    vector<int>L(n+1);
    for(int i=1;i<=n;i++)
    {
        if(i==1) L[i]=0;
        else
        {
            if(a[i-1]==1) L[i]=L[i-1];
            else L[i]=i-2;
        }
    }
    vector<int>pre(n+1);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+(a[i]==0);
    auto check = [&] (int x)
    {
        vector<vector<int>>dp(n+1,vector<int>(k+1,1e8));
        dp[0][0]=0;
        for(int i=1;i<=n;i++)
        {
            dp[i]=dp[i-1];
            int lst=i-x+1;
       
            if(lst>=1)
            {
                int val=pre[i]-pre[lst-1];
                
                for(int j=0;j<k;j++)
                {
                    dp[i][j+1]=min(dp[i][j+1],dp[L[lst]][j]+val);
                }
            }
        }
        
        return (dp[n][k]<=m);
    };
    //是否存在使大于等于x的木棒的个数为k的最小更改数
    
    int l=1,r=n,ans=-1;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans<<'\n';
    return 0;
}