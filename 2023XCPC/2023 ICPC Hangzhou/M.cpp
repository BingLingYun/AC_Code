#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

void solve()
{
    int n;cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<i64>pre(n+1);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
    int pos=0;
    for(int i=2;i<n;i++)
    {
        if(a[i]<a[i-1] && a[i]<a[i+1])
        {
            pos=i;break;
        }
    }
    double ans=0;
    ans=max(ans,1.0*(a[pos-1]+a[pos]+a[pos+1])/3);
    ans=max(ans,1.0*pre[pos+1]/(pos+1));
    ans=max(ans,1.0*(pre[n]-pre[pos-2])/(n-pos+2));
    ans=max(ans,1.0*pre[n]/n);
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);
    cout<<fixed<<setprecision(15);

    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}