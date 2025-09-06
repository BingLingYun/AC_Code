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
    cout<<fixed<<setprecision(15);
    
    i64 n,m;cin>>n>>m;
    vector<array<int,3>>a(n+1);
    for(int i=1;i<=n;i++)
    {
        int w,l,r;cin>>w>>l>>r;
        a[i]={w,l,r};
    }
    sort(a.begin()+1,a.end(),[&](const auto x,const auto y){
        return x[0]>y[0];
    });
    i64 ans=0,c=0;
    i64 sum=0;
    for(int i=1;i<=n;i++)
    {
        sum+=1ll*a[i][1]*a[i][0];
        c+=a[i][1];
    }
    vector<i64>cnt(n+1),pre(n+1);
    for(int i=1;i<=n;i++)
    {
        cnt[i]=a[i][2]-a[i][1];
        pre[i]=pre[i-1]+cnt[i]*a[i][0];
        cnt[i]+=cnt[i-1];
    }
    for(int i=1;i<=n;i++)
    {
        i64 now=sum-(1ll*a[i][1]*a[i][0]);
        i64 h=m-(c-a[i][1]);
        int l=1,r=i-1,res=0;
        while(l<=r)
        {
            int mid=l+r>>1;
            if(cnt[mid] <= h) res=mid,l=mid+1;
            else r=mid-1;
        }
        now+=pre[res];
        h-=cnt[res];
        now+=1ll*h*a[res+1][0];
        ans=max(ans,now);
    }
    cout<<ans<<"\n";
    return 0; 
}