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
struct node{
    i64 T,A,B;
};
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int n;cin>>n;
    vector<node>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i].T>>a[i].A>>a[i].B;
    sort(a.begin()+1,a.end(),[&](const node &x,const node &y){
        return x.B*x.T*(y.B-y.A) < y.B*y.T*(x.B-x.A);
    });
    // for(int i=1;i<=n;i++) cout<<a[i].T<<" "<<a[i].A<<" "<<a[i].B<<"\n";
    vector<i64>p(n+1,1);
    for(int i=1;i<=n;i++)
    {
        i64 x = a[i].A*fpow(a[i].B,mod-2)%mod;
        p[i]=p[i-1]*x%mod;
    }
    // for(int i=1;i<=n;i++) cout<<p[i]<<" ";cout<<"\n";
    i64 base = fpow(p[n],mod-2)%mod;
    i64 ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=(ans + a[i].T*p[i-1]%mod*base%mod)%mod;
    }
    cout<<ans<<"\n";
    return 0;
}