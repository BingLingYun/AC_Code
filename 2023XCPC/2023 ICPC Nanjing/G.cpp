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
    
    int n,W,k;cin>>n>>W>>k;
    vector<pii>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i].first>>a[i].second;
    sort(a.begin()+1,a.end());
    vector<i64>suf(n+2);
    multiset<int>st;
    i64 sum=0;
    for(int i=n;i>=1;i--)
    {
        st.insert(a[i].second);
        sum+=a[i].second;
        if(st.size()>k)
        {
            int val=*st.begin();
            sum-=val;
            st.erase(st.begin());
        }
        suf[i]=sum;
    }
    i64 ans=0;
    vector<i64>dp(W+1);
    for(int i=1;i<=n;i++)
    {
        auto [w,v]=a[i];
        for(int j=W;j>=w;j--)
        {
            dp[j]=max(dp[j],dp[j-w]+v);
        }
        ans=max(ans,dp[W]+suf[i+1]);
    }
    cout<<ans<<"\n";
    return 0;
}