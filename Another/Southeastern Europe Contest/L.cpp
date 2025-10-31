#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int,int> pii;

struct BIT{
    vector<int>a;int n;
    BIT(){}
    BIT (int n)
    {
        this->n=n;
        init(n);
    }
    void init(int n)
    {
        a.resize(n+10,0);
    }
    void add(int x,int v)
    {
        for(int i=x;i<=n;i+=(i&(-i))) a[i]+=v;
    }
    int ask(int x)
    {
        int res=0;
        for(int i=x;i>0;i-=(i&(-i))) res+=a[i];
        return res;
    }
};
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n;cin>>n;
    vector<int>a(n+1),pos(n+1);
    for(int i=1;i<=n;i++) cin>>a[i],pos[a[i]]=i;
    int now=n;
    vector<int>vec;
    for(int i=n;i>=1;i--)
    {
        if(a[i]==now)
        {
            now--;
        }
    }
    BIT bit(n);
    vector<pii> ans;
    for(int i=now;i>=1;i--)
    {
        int p = pos[i];
        int np = bit.ask(p)+p;
        ans.push_back({np,1});
        bit.add(1,1);
        bit.add(p+1,-1);
    }
    cout<<ans.size()<<" "<<ans.size()<<"\n";
    for(auto [x,y]:ans) cout<<x<<" "<<y<<"\n";
    return 0;
}