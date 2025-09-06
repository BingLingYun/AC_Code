#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef long long i64;

struct BIT
{
    vector<int>a;int n;
    BIT(int n)
    {
        a.resize(n+1);
        this->n=n;
    }
    void add(int x,int v)
    {
        for(int i=x;i<=n;i+=(i&(-i)))
        {
            a[i]+=v;
        }
    }
    int ask(int x)
    {
        int res=0;
        for(int i=x;i;i-=(i&(-i)))
        {
            res+=a[i];
        }
        return res;
    }
};

void solve()
{
    int n;cin>>n;
    vector<pii>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i].first;
    for(int i=1;i<=n;i++) cin>>a[i].second;
    sort(a.begin()+1,a.end());
    BIT bit(n);
    i64 res=0;
    for(int i=n;i>=1;i--)
    {
        res+=bit.ask(a[i].second);
        bit.add(a[i].second,1);
        // cout<<a[i].second<<" ";/
    }
    // cout<<"\n";
    // cout<<res<<"\n";
    int op=(res&1);
    if(op&1) cout<<"A";
    else cout<<"B";
    for(int i=1;i<=n-1;i++)
    {
        char ch;cin>>ch;
        int l,r,d;cin>>l>>r>>d;
        i64 now = 1ll*(r-l)*d;
        int ck=(now&1);
        op^=ck;
        if(op&1) cout<<"A";
        else cout<<"B";
    }
    cout<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}