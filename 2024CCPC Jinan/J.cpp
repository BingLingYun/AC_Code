#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

const int maxn=1e5+10;

int x[maxn],y[maxn],z[maxn],vec[3*maxn];
void solve()
{
    int n;cin>>n;
    vector<array<int,3>>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i][0]>>a[i][1]>>a[i][2];
    set<int>s,t;
    for(int i=1;i<=n;i++)
    {
        x[a[i][0]]++;
        y[a[i][1]]++;
        z[a[i][2]]++;
        s.insert(a[i][0]);
        s.insert(a[i][1]);
        s.insert(a[i][2]);
    }
    for(int i=1;i<=n;i++)
    {
        if(x[a[i][0]] >= y[a[i][1]] && x[a[i][0]]>=z[a[i][2]])
        {
            vec[a[i][0]]+=1;t.insert(a[i][0]);
        }
        else if(x[a[i][0]] <= y[a[i][1]] && y[a[i][1]]>=z[a[i][2]])
        {
            vec[maxn+a[i][1]]+=1;t.insert(maxn+a[i][1]);
        }
        else if(z[a[i][2]] >= y[a[i][1]] && x[a[i][0]]<=z[a[i][2]])
        {
            vec[2*maxn+a[i][2]]+=1;t.insert(2*maxn+a[i][2]);
        }
    }
    int ans=0;
    vector<pii>line;
    for(auto i:s)
    {
        line.push_back({x[i],i});
        line.push_back({y[i],maxn+i});
        line.push_back({z[i],2*maxn+i});
    }
    sort(line.begin(),line.end());
    int l=0;
    for(int j=0;j<=n-1;j++)
    {
        while(l<line.size() && line[l].first<=j)
        {
            ans+=vec[line[l].second];
            l++;
        }
        cout<<ans<<" ";
    }
    cout<<"\n";
    for(auto i:s) x[i]=y[i]=z[i]=0;
    for(auto i:t) vec[i]=0; 
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