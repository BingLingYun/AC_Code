#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=1e9+7;

multiset<i64>s,t;
i64 sum1=0,sum2=0;
void eval()
{
    if(s.size())
    {
        auto itr=s.end();itr--;
        sum1-=*itr;sum2+=*itr;
        t.insert(*itr);s.erase(itr);
    }
    while(s.size()<t.size())
    {
        sum1+=*t.begin();sum2-=*t.begin();
        s.insert(*t.begin());
        t.erase(t.begin());
    }
}
i64 getsum()
{
    i64 now=1ll*(i64)s.size()*(*s.rbegin())-sum1;
    now+=sum2-1ll*(i64)(t.size())*(*s.rbegin());
    return now;
}
void erase(i64 x)
{
    if(s.empty())
    {
        t.erase(t.lower_bound(x)),sum2-=x;
    }
    else
    {
        auto itr=s.end();itr--;
        if(*itr<x) t.erase(t.lower_bound(x)),sum2-=x;
        else s.erase(s.lower_bound(x)),sum1-=x;
    }
    
}
void solve()
{
    i64 n,k;cin>>n>>k;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<i64>val(n+1);
    for(int i=1;i<=n;i++) val[i]=a[i]-i;
    s.clear();t.clear();sum1=sum2=0;
    int ans=1;
    for(int i=1,j=0;i<=n;i++)
    {
        while(j<n)
        {
            j++;
            s.insert(val[j]);sum1+=val[j];
            eval();
            i64 now=getsum();
            if(now<=k) continue;
            else
            {
                erase(val[j]);
                j--;break;
            }
        }
        ans=max(ans,(int)s.size()+(int)t.size());
        erase(val[i]);
    }
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}

