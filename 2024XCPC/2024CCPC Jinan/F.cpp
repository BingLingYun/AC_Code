#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
#define all(x) x.begin(),x.end()
using namespace std;

constexpr i64 mod=998244353;

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
struct Combi{
    vector<i64>fac,inv;int n;
    Combi(int m)
    {
        fac=vector<i64>(m+1);
        inv=vector<i64>(m+1);
        n=m;
    }
    void init()
    {
        fac[0]=1;
        for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
        inv[n]=fpow(fac[n],mod-2);
        for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
    }
    i64 C (i64 x,i64 y)
    {
        if(x<y) return 0ll;
        return (fac[x]*inv[y]%mod*inv[x-y]%mod);
    }
};
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout<<fixed<<setprecision(15);

    int m,n;cin>>m>>n;
    vector<vector<i64>>f(m+1,vector<i64>(21));
    for(int i=1;i<=m;i++)
    {
        f[i][1]=1;
        for(int j=i+i;j<=m;j+=i)
        {
            for(int k=2;k<=20;k++)
            {
                f[j][k]=(f[j][k]+f[i][k-1])%mod;
            }
        }
    }
    Combi ca(m);ca.init();
    i64 res=0;
    for(int i=1;i<=m;i++)
    {
        int cnt=m/i-1;
        i64 val=0;
        for(int j=1;j<=min(20,n);j++)
        {
            val=(val+f[i][j]*ca.C(cnt,n-j)%mod)%mod;
        }
        (res+=val)%=mod;
    }
    i64 ans=ca.C(m,n)*n%mod;
    ans=(ans-res+mod)%mod;
    cout<<ans<<"\n";
    return 0; 
}
