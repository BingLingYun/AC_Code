#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;
constexpr i64 mod=998244353;

struct Info{
    vector<i64>A;
    i64 sm;
    set<pll>st;
    Info(int N)
    {
        A=vector<i64>(N+10);
        sm=0;
        st.insert({1,0});
        st.insert({N+1,1e17});
    }
    void update(int x,int v)
    {
        A[x]+=v;
        auto it=prev(st.upper_bound({x,1e17}));

        if(it->second >= A[x]) return ;
        sm -= (next(it)->first - it->first) * it->second;
        sm += (x - it->first) * it->second + (next(it)->first - x) * A[x];
        it = st.insert({x, A[x]}).first;
        while (next(it)->second <= A[x]) 
        {
            sm -= (next(it)->first - x) * A[x] + (next(next(it))->first - next(it)->first) * next(it)->second;
            st.erase(next(it));
            sm += (next(it)->first - x) * A[x];
        }
    }
};
void solve()
{
    int n;cin>>n;
    i64 sum=0,mx=0;
    vector<i64>a(n+1);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];mx=max(mx,a[i]);
    }
    Info f(n);Info g(n);
    for(int i=1;i<=n;i++)
    {
        f.update(i,a[i]);
        g.update(n-i+1,a[i]);
    }
    int q;cin>>q;
    while(q--)
    {
        int x,v;cin>>x>>v;
        a[x]+=v;
        mx=max(mx,a[x]);
        sum+=v;
        f.update(x,v);
        g.update(n-x+1,v);
        i64 res=f.sm+g.sm-1ll*n*mx-sum;
        cout<<res<<"\n";
    }
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