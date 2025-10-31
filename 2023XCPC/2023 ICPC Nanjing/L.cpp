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
    
    int t;cin>>t;
    while(t--)
    {
        i64 n,k;cin>>n>>k;
        vector<array<int,3>>a(n+1);
        for(int i=1;i<=n;i++)
        {
            int c,w,f;cin>>c>>w>>f;
            a[i]={c,w,f};
        }
        sort(a.begin()+1,a.end(),[&](const auto &x,const auto &y){
            return x[2]>y[2];
        });
        i64 ans=0;
        i64 yu=0,h=0;
        for(int i=1;i<=n;i++)
        {
            i64 val=a[i][0]*a[i][1];
            i64 lst=a[i][2];
            if(val<=yu)
            {
                yu-=val;
            }
            else
            {
                val-=yu;
                ans+=h;
                i64 cnt=val/k;
                yu=(k-val%k)%k;
                if(yu==0) h=0;
                else h=lst;
                ans+=cnt*lst;
            }
        }
        ans+=h;
        cout<<ans<<"\n";
    }
    return 0;
}