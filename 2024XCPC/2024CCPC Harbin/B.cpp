#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

struct Point{
    i64 x,y;
    int id;
    Point(i64 x = 0,i64 y = 0) : x(x), y(y) {}
    Point &operator+=(const Point &rhs) {
        x += rhs.x; y += rhs.y;
        return *this;
    }
    Point &operator-=(const Point &rhs) {
        x -= rhs.x; y -= rhs.y;
        return *this;
    }
    friend Point operator+(const Point &lhs, const Point &rhs) { //+
        return Point(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    friend Point operator-(const Point &lhs, const Point &rhs) { //-
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }
    friend Point operator*(const Point &lhs, double t){ //数乘
        return Point(lhs.x * t, lhs.y * t);
    }
    friend Point operator/(const Point &lhs, double t){ //数乘
        return Point(lhs.x / t, lhs.y / t);
    }
    //叉积可以用来判断rhs在lhs的方向,顺时针<0,逆时针>0
    friend double operator*(const Point &lhs, const Point &rhs){ //叉积 a,b为向量
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }
    friend double operator&(const Point &lhs, const Point &rhs){ //点积 a,b为向量
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    friend bool operator<(const Point &lhs, const Point &rhs){ //点积 a,b为向量
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    }
};
i64 cross(Point a,Point b,Point c){ //叉积 a,b,c为点,b-a,c-a向量叉积
    return (b - a) * (c - a);
}
i64 getarea(Point a,Point b,Point c){//求三角形面积
    return abs((b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y));
}

void solve()
{
    int n,top,tot;cin>>n;
    vector<Point>p(n+1),s(2*n+1);
    for(int i=1;i<=n;i++)
    {
        cin>>p[i].x>>p[i].y;
        p[i].id=i;
    }
    auto Andrew = [&] ()
    {
        top=tot=0;
        sort(p.begin()+1,p.end());//排序
        for(int i=1;i<=n;i++){//下凸包
            while(top>1&&cross(s[top-1],s[top],p[i])<=0) top--;
            s[++top]=p[i];
        }
        int t=top;
        for(int i=n-1;i>=1;i--){//上凸包
            while(top>t&&cross(s[top-1],s[top],p[i])<=0) top--;
            s[++top]=p[i];
        }
        tot=top-1;
    };//求凸包
    Andrew();
    if(tot==n)
    {
        cout<<-1<<"\n";
        return;
    }
    i64 ans=0,res=0;
    for(int i=2;i<=tot-1;i++)
    {
        ans+=getarea(s[1],s[i],s[i+1]);
    }
    vector<int>vis(n+1);
    for(int i=1;i<=tot;i++)
    {
        vis[s[i].id]=1;
    }
    int m=n-tot;
    vector<Point>a(m+1),b(2*m+1);
    m=0;
    for(int i=1;i<=n;i++)
    {
        if(vis[p[i].id]) continue;
        a[++m]=p[i];
    }
    if(tot+2>=n)
    {
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=tot;j++)
            {
                int k=(j%tot)+1;
                i64 val=getarea(s[j],s[k],a[i]);
                res=max(res,ans-val);
            }
        }
    }
    else
    {
        int top2=0,tot2=0;
        sort(a.begin()+1,a.end());//排序
        for(int i=1;i<=m;i++){//下凸包
            while(top2>1&&cross(b[top2-1],b[top2],a[i])<=0) top2--;
            b[++top2]=a[i];
        }
        int t=top2;
        for(int i=m-1;i>=1;i--){//上凸包
            while(top2>t&&cross(b[top2-1],b[top2],a[i])<=0) top2--;
            b[++top2]=a[i];
        }
        tot2=top2-1;
        int pos=1;
        for(int i=1;i<=tot;i++)
        {
            int j=i%tot+1;
            while(1)
            {
                int c=pos%tot2+1;
                i64 val1=getarea(s[i],s[j],b[pos]);
                res=max(res,ans-val1);
                i64 val2=getarea(s[i],s[j],b[c]);
                res=max(res,ans-val2);
                if(val1>=val2) pos=c;
                else break;
            }
        }
    }
    cout<<res<<"\n";
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