#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;
constexpr i64 mod=998244353;

void solve()
{
    int n,m;cin>>n>>m;
    vector<pii>a(m+1);
    for(int i=1;i<=m;i++)
    {
        cin>>a[i].first>>a[i].second;
    }
    sort(a.begin()+1,a.end());
    for(int i=1;i<=m;i++)
    {
        if(a[i].second==0) continue;
        if(a[i].first==a[i-1].first && a[i].second==a[i-1].second) continue;
        int len=a[i].first-a[i-1].first;
        if(a[i-1].second>=a[i].second)
        {
            if(a[i].second+1<=len) continue;
            else 
            {
                cout<<"No"<<"\n";return;
            }
        }
        else
        {
            if(a[i-1].second+len==a[i].second) continue;
            if(a[i].second+1<=len) continue;
            cout<<"No"<<"\n";return;
        }
    }
    cout<<"Yes"<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(20);
    
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;    
}