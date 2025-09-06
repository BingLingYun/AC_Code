#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef long long i64;

struct ST{
    vector<vector<pii>>f;
    int n;
    ST(){}
    ST(int n)
    {
        init(n);
    }
    void init(int n)
    {
        this->n=n;
        f.resize(n+1,vector<pii>(31));
    }
    pii quiry(int l,int r)
    {
        int ln=(int)(log(r-l+1)/log(2));
        if(f[l][ln].first > f[r-(1<<ln)+1][ln].first) return f[r-(1<<ln)+1][ln];
        else return f[l][ln];
    }
    void build(vector<int>a)
    {
        for(int i=1;i<=n;i++)
        {
            f[i][0].first=a[i];
            f[i][0].second=i;
        }
        int len=(int)(log(n)/log(2));
        for(int j=1;j<=len;j++)
        {
            for(int i=1;i<=n-(1<<j)+1;i++)
            {
                if(f[i][j-1].first > f[i+(1<<(j-1))][j-1].first) f[i][j]=f[i+(1<<(j-1))][j-1];
                else f[i][j]=f[i][j-1];
            }
        }
    }
};
void solve()
{
    int n,m;cin>>n>>m;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    ST rmq(n);rmq.build(a);
    vector<vector<int>>g(n+1);
    function<int(int,int)> build = [&] (int l,int r)
    {
        if(l==r) return l;
        auto val=rmq.quiry(l,r);
        int pos=val.second;
        if(pos>l) g[pos].push_back(build(l,pos-1));
        if(pos<r) g[pos].push_back(build(pos+1,r));
        return pos;
    };
    int root = build(1,n);
    int mn=1e9+10;
    for(int i=1;i<=n;i++)
    {
        mn=min(mn,a[i]);
    }

    int gc=0;
    for(int i=1;i<n;i++)
    {
        gc = __gcd(gc,abs(a[i]-a[i+1]));
    }
    if(gc==0)
    {
        cout<<m<<" "<<1ll*(m+1)*m/2<<"\n";
        return;
    }
    vector<int>d;
    for(int i=1;i*i<=gc;i++)
    {
        if(gc%i) continue;
        d.push_back(i);
        if(i*i!=gc)
        {
            d.push_back(gc/i);
        }
    }
    vector<int>b(n+1);
    auto check = [&] (int x)
    {
        for(int i=1;i<=n;i++) b[i]=a[i]+x;
        for(int i=1;i<=n;i++)
        {
            for(auto j:g[i])
            {
                if(b[j]%b[i]) return 0;
            }
        }
        return 1;
    };
    i64 cnt=0,sum=0;
    for(auto val:d)
    {
        int x=val-mn;
        if(x<1 || x>m) continue;
        int ret=check(x);
        if(ret) cnt++,sum+=x;
    }
    cout<<cnt<<" "<<sum<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}