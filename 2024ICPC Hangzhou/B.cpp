#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

i64 FULL;
struct Info{
	i64 f,g,tag;
    int l,r;
};
Info operator + (Info lson,Info rson)
{
    Info u;
    u.g = lson.g & rson.g;
    u.f = (lson.g & rson.f) | (lson.f & rson.g);
    u.tag = FULL;
    u.l = lson.l;u.r = rson.r;
    return u;
}
struct SegmentTree{
    vector<Info>info;
    vector<i64>a,b;
    int n;
    SegmentTree(int n)
    {
        init(n);
	}
    void init(int n)
    {
        this->n=n;
        info.resize(n<<2);
        a.resize(n+1);
        b.resize(n+1);
    }
    void initarray(vector<i64>v)
    {
        a=v;
        for(int i=1;i<=n;i++)
        {
            b[i]=a[i]^FULL;
        }
    }
    void pushup(int u)
    {
        info[u]=info[u<<1]+info[u<<1|1];
    }
    void build(int u,int l,int r)//建树
    {
        info[u].l=l,info[u].r=r;
        if(l==r)
        {
            info[u].f=b[l];
            info[u].g=a[l];
            info[u].tag=FULL;
            return;
        }
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
  		pushup(u);
    }
    void pushdown(int u)//标记下移
    {
        if(info[u].tag!=FULL)
        {
            auto &ls = info[u<<1];
            auto &rs = info[u<<1|1];
            i64 tag = info[u].tag;
            ls.g = ls.g & tag;
            rs.g = rs.g & tag;
            ls.tag = ls.tag & tag;
            rs.tag = rs.tag & tag; 
            ls.f = ls.f & tag;
            rs.f = rs.f & tag;
            if(ls.l==ls.r)
            {
                ls.f = FULL ^ ls.g;
            }
            if(rs.l==rs.r)
            {
                rs.f = FULL ^ rs.g;
            }
            info[u].tag = FULL;
        }
    }
    void modify(int u,int l,int r,int x,int y,i64 k)//当前区间与目的区间
    {
        if(r<x || l>y) return;
        if(x<=l && r<=y)
        {
            info[u].g=info[u].g&k;
            info[u].f=info[u].f&k;
            info[u].tag = info[u].tag&k;
            if(l==r)
            {
                info[u].f = info[u].g ^ FULL;
            }
            return;
        }
        pushdown(u);
        int mid=l+r>>1;
        if(x<=mid) modify(u<<1,l,mid,x,y,k);
        if(y>mid) modify(u<<1|1,mid+1,r,x,y,k);
        pushup(u);
    }
    void modify(int u,int l,int r,int pos,i64 k)//当前区间与目的区间
    {
        if(l==pos && r==pos)
        {
            info[u].tag=FULL;
            info[u].g=k;
            info[u].f = info[u].g^FULL;
            return;
        }
        pushdown(u);
        int mid=l+r>>1;
        if(pos<=mid) modify(u<<1,l,mid,pos,k);
        if(pos>mid) modify(u<<1|1,mid+1,r,pos,k);
        pushup(u);
    }
    Info quiry(int u,int l,int r,int x,int y)
    {
        if(x<=l && r<=y)
        {
            return info[u];
        }
        pushdown(u);
        int mid=l+r>>1;
        if(y<=mid) return quiry(u<<1,l,mid,x,y);
        else if(x>mid) return quiry(u<<1|1,mid+1,r,x,y);
        return quiry(u<<1,l,mid,x,y)+quiry(u<<1|1,mid+1,r,x,y);
    }
    int binary(int u,int l,int r,int x,int pos)
    {
        if(info[u].g>>pos&1) return 0;
        if(l==r) return l;
        int mid=l+r>>1;
        pushdown(u);
        if(x<=l)
        {
            if(info[u<<1].g >> pos&1) return binary(u<<1|1,mid+1,r,x,pos);
            else return binary(u<<1,l,mid,x,pos);
        }
        else if(mid<x)
        {
            return binary(u<<1|1,mid+1,r,x,pos);
        }
        else
        {
            int t=binary(u<<1,l,mid,x,pos);
            if(!t) t=binary(u<<1|1,mid+1,r,x,pos);
            return t;
        }
    }
};
void solve()
{
    FULL = (1ll<<63)-1;
    int n,q;cin>>n>>q;
    vector<i64>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    SegmentTree segment(n);segment.initarray(a);
    segment.build(1,1,n);
    while(q--)
    {
        int op;cin>>op;
        if(op==1)
        {
            int l,r;i64 x;cin>>l>>r>>x;
            segment.modify(1,1,n,l,r,x);
        }
        else if(op==2)
        {
            int x;i64 val;cin>>x>>val;
            segment.modify(1,1,n,x,val);
        }
        else
        {
            int l,r;cin>>l>>r;
            auto res = segment.quiry(1,1,n,l,r);
            if(res.f==0)
            {
                cout<<res.g<<"\n";
            }
            else
            {
                for(int i=62;i>=0;i--)
                {
                    if(res.f>>i&1)
                    {
                        auto pos = segment.binary(1,1,n,l,i);
                        i64 ans=FULL;
                        if(pos>l) ans &= segment.quiry(1,1,n,l,pos-1).g;
                        if(pos<r) ans &= segment.quiry(1,1,n,pos+1,r).g;
                        cout<<ans<<"\n";
                        break;
                    }
                }
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}