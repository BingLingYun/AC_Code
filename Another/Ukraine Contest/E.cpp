#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

constexpr i64 mod = 998244353;

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
    Combi(){}
    Combi(int n)
    {
        init(n);
    }
    void init(int n)
    {
        this->n=n;
        fac.resize(n+1,0);
        inv.resize(n+1,0);
    }
    void init_C()
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
void solve()
{
    int n,m;cin>>n>>m;
    // i64 ans=0;
    Combi ca(n+m);ca.init_C();

    // for(int j=1;j<=m;j++)
    // {
    //     for(int i=1;i<=n;i++)
    //     {
    //         i64 res1 = ca.C(n,i)*fpow(m-j,i)%mod*fpow(j,n-i)%mod;
    //         ans=(ans+res1)%mod;
    //     }
    // }
    i64 ans2=0;

    for(int j=1;j<=m;j++)
    {
        ans2=(ans2+fpow(m,n))%mod;
        ans2 = (ans2 - fpow(j,n)+mod)%mod;
    }
    // ans2=(ans2-1+mod)%mod;
    // assert(ans2==ans);
    ans2 = ans2*2%mod;
    // ans2 += fpow()/
    ans2+=fpow(m,n);ans2%=mod;
    cout<<ans2<<"\n";
}
int main()
{
    int t=1;
    // cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}