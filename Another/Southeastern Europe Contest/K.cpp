#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int,int> pii;

struct Info{
	i64 tag,sum;
};
Info operator + (Info a,Info b)
{
    Info c;c.tag=1;
    c.sum=a.sum+b.sum;
    return c;
}
struct SegmentTree{
    vector<Info>info;
    SegmentTree(int n)
    {
        init(n);
	}
    void init(int n)
    {
        info.resize(n<<2);
    }
    void pushup(int u)
    {
        info[u]=info[u<<1]+info[u<<1|1];
    }
    void build(int u,int l,int r)//建树
    {
        if(l==r)
        {
            info[u].tag=1;
            info[u].sum=1;
            return;
        }
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
  		pushup(u);
    }
    void pushdown(int u)//标记下移
    {
        info[u<<1].sum=info[u<<1].sum*info[u].tag;
        info[u<<1|1].sum=info[u<<1|1].sum*info[u].tag;
        info[u<<1].tag=info[u<<1].tag*info[u].tag;
        info[u<<1|1].tag=info[u<<1|1].tag*info[u].tag;
        info[u].tag=1;
    }
    void modify(int u,int l,int r,int x,int y,i64 k)//当前区间与目的区间
    {
        if(r<x || l>y) return;
        if(x<=l && r<=y)
        {
            info[u].tag*=k;info[u].sum*=k;
            return;
        }
        pushdown(u);
        int mid=l+r>>1;
        if(x<=mid) modify(u<<1,l,mid,x,y,k);
        if(y>mid) modify(u<<1|1,mid+1,r,x,y,k);
        pushup(u);
    }
    void modify(int u,int l,int r,int pos,i64 len)//当前区间与目的区间
    {
        if(r<pos || l>pos) return;
        if(l==pos && r==pos)
        {
            info[u].tag=1;info[u].sum+=len;
            return;
        }
        pushdown(u);
        int mid=l+r>>1;
        if(pos<=mid) modify(u<<1,l,mid,pos,len);
        if(pos>mid) modify(u<<1|1,mid+1,r,pos,len);
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
};

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n,q;cin>>n>>q;
    string s;cin>>s;
    s=" "+s;
    SegmentTree segment(n+1);segment.build(1,1,n);
    while(q--)
    {
        int op;cin>>op;
        if(op==1)
        {
            i64 l,r;cin>>l>>r;
            int L1=1,R1=n,res1=-1;
            while(L1<=R1)
            {
                int mid=L1+R1>>1;
                auto ans = segment.quiry(1,1,n,1,mid);
                if(ans.sum >= l) res1=mid,R1=mid-1;
                else L1=mid+1;
            }
            int L2=1,R2=n,res2=-1;
            while(L2<=R2)
            {
                int mid=L2+R2>>1;
                auto ans = segment.quiry(1,1,n,1,mid);
                if(ans.sum >= r) res2=mid,R2=mid-1;
                else L2=mid+1;
            }
            if(res1==res2)
            {
                segment.modify(1,1,n,res1,r-l+1);
                continue;
            }
            if(res2>res1)
            {
                auto sum2 = segment.quiry(1,1,n,1,res2-1);
                i64 len2 = r-sum2.sum;
                segment.modify(1,1,n,res2,len2);
            }
            auto sum1 = segment.quiry(1,1,n,1,res1);
            i64 len1 = sum1.sum-l+1;
            segment.modify(1,1,n,res1,len1);
            if(res1+1<=res2-1)
            {
                segment.modify(1,1,n,res1+1,res2-1,2);
            }
        }
        else
        {
            i64 x;cin>>x;
            int L=1,R=n,res=-1;
            while(L<=R)
            {
                int mid=L+R>>1;
                auto ans = segment.quiry(1,1,n,1,mid);
                if(ans.sum >= x) res=mid,R=mid-1;
                else L=mid+1;
            }
            // cout<<res<<"\n";
            cout<<s[res]<<"\n";
        }
    }
    return 0;
}