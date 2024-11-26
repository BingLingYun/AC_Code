#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
#define all(x) x.begin(),x.end()
using namespace std;

constexpr i64 mod=1e9+7;

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
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);

    int n,m;cin>>n>>m;
    vector<i64>x(n+1),v(m+1),inv(n+1),invv(m+1);
    for(int i=1;i<=n;i++)
    {
        cin>>x[i];
        inv[i]=fpow(i,mod-2);
    }
    for(int i=1;i<=m;i++)
    {
        cin>>v[i];
        invv[i]=fpow(v[i],mod-2);
    }
    vector<pii>t;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            t.push_back({j,i});
        }
    }
    sort(all(t),[&](auto A,auto B){
        return -x[A.second]*v[B.first] < -x[B.second]*v[A.first];
    });
    vector<i64>dp(m+1),cnt(m+1);
    i64 ans=0;dp[0]=1;
    for(auto p:t)
    {
        int ball=p.first,pos=p.second;
        for(int i=0;i<m;i++)
        {
            dp[i]=dp[i]*n%mod*inv[(n-cnt[ball])]%mod;
            dp[i+1]=(dp[i+1]-dp[i]*cnt[ball]%mod*inv[n]%mod+mod)%mod;
        }
        i64 t=(-x[pos])*invv[ball]%mod;
        (ans+=dp[m/2]*t%mod)%=mod;
        cnt[ball]+=1;
        for(int i=m-1;i>=0;i--)
        {
            dp[i+1]=(dp[i+1]+dp[i]*cnt[ball]%mod*inv[n]%mod)%mod;
            dp[i]=dp[i]*(n-cnt[ball])%mod*inv[n]%mod;
        }
    }
    ans=ans*inv[n]%mod;
    cout<<ans<<"\n";
    return 0; 
}
