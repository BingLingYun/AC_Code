#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;
constexpr i64 mod=998244353;

void solve()
{
    int n;cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<pii>ans;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==i) continue;
        int pos=0;
        for(int j=n;j>i;j--)
        {
            if(a[j]<a[i])
            {
                pos=j;break;
            }
        }
        set<int>st;
        for(int j=i;j<=pos;j++) st.insert(a[j]);
        ans.push_back({i,pos});
        for(int j=i;j<=pos;j++)
        {
            a[j]=*st.begin();
            st.erase(st.begin());
        }
    }
    cout<<ans.size()<<"\n";
    for(auto [x,y]:ans) cout<<x<<" "<<y<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(10);
    
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;    
}