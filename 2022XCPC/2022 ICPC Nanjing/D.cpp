#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

const i64 mod = 998244353;

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
        a.resize(n+1,0);
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
    int ask(int l,int r)
    {
        return ask(r)-ask(l-1);
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(10);

    int n,k,m,c,d;cin>>n>>k>>m>>c>>d;
    vector<i64>a(n+1),b(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        b[i]=a[i]+c+1ll*(i-1)*d;
    }
    auto tmp=b;
    sort(tmp.begin()+1,tmp.end());
    tmp.erase(unique(tmp.begin()+1,tmp.end()),tmp.end());
    vector<int>id(n+1);
    for(int i=1;i<=n;i++)
    {
        int cc = lower_bound(tmp.begin()+1,tmp.end(),b[i])-tmp.begin();
        id[i]=cc;
    }
    
    auto check = [&] (i64 x)
    {
        vector<int>pre(n+2),suf(n+2);
        for(int i=1;i<=n;i++)
        {
            pre[i]=pre[i-1]+(a[i]>=x);
        }
        for(int i=n;i>=1;i--)
        {
            suf[i]=suf[i+1]+(a[i]>=x);
        }
        if(pre[n]>=k) return true;

        BIT bit(n+5);
        for(int i=1;i<m;i++)
        {
            bit.add(id[i],1);
        }
        for(int i=m;i<=n;i++)
        {
            bit.add(id[i],1);
            i64 now = x + 1ll*(i-m)*d;
            int cc = lower_bound(tmp.begin()+1,tmp.end(),now)-tmp.begin()-1;
            int res = pre[i-m] + suf[i+1] + m-bit.ask(cc);
            if(res>=k) return true;
            bit.add(id[i-m+1],-1);
        }
        return false;
    };
    i64 l=0,r=1e16,res=-1;
    while(l<=r)
    {
        i64 mid=l+r>>1;
        if(check(mid)) res=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<res<<"\n";
    return 0;
}