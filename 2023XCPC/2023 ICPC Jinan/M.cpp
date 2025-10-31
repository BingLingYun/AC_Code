#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

const double eps=1e-9; 
const double PI=acos(-1.0);
struct Point{
    long double x,y;
    Point(long double x = 0,long double y = 0) : x(x), y(y) {}
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
    double len() const{ //向量的模
        return sqrt(x * x + y * y);
    }
    void zero(){  //判断是否是0
        if(fabs(x)<=eps) x=0;
        if(fabs(y)<=eps) y=0;
    }
};
Point norm(Point a){ //单位向量
    return a/a.len();
}
long double dis(Point a,Point b){ //两点间距离
    return (a-b).len();
}
double cross(Point a,Point b,Point c){ //叉积 a,b,c为点,b-a,c-a向量叉积
    return (b - a) * (c - a);
}
double dot(Point a,Point b,Point c){ //点积 a,b,c为点,b-a,c-a向量点积
    return (b - a) & (c - a);
}
double angle(Point a,Point b){ //求夹角

    return acos((a & b) / a.len() / b.len());
}
double angle(Point a,Point b,Point c){ // 求向量ab,ac的夹角
    Point x=b-a,y=c-a;
    // cout<<x.x<<" "<<x.y<<"\n";
    // cout<<y.x<<" "<<y.y<<"\n";
    return angle(b-a,c-a);
}
//获取两直线的交点,其中a,b为点,u,v为a和b的方向向量
Point cross(Point a,Point u,Point b,Point v){
    double t = (a - b) * v / (v * u);
    return a + u * t;
}
Point rotate(Point a,double b){ //逆时针转b角
    return Point(a.x*cos(b)-a.y*sin(b),a.x*sin(b)+a.y*cos(b));
}
//判断线段ab与线段cd是否相交 0为不相交,1为相交
bool intersect(Point a,Point b,Point c,Point d){
    if(cross(a , b , c)*cross(a , b , c) > 0) return 0;
    if(cross(c , d , a)*cross(c , d , b) > 0) return 0;
    return 1;
}
pair<Point,Point> midperp(Point a,Point b){ //中垂线,方向a->b逆时针转90度
    return {(a+b)/2,rotate(b-a,PI/2)}; 
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);
    
    int n;cin>>n;
    vector<Point>p(n+1),s(2*n+1);
    vector<int>id(2*n+1),vis(n+1);
    int top=0,tot=0; //s栈
    //凸包板子,tot是凸包上的点数,tot+1为第一个点
    auto Andrew = [&] (){
        top=tot=0;
        sort(p.begin()+1,p.end());//排序
        for(int i=1;i<=n;i++){//下凸包
            while(top>1&&cross(s[top-1],s[top],p[i])<=0) top--;
            s[++top]=p[i];id[top]=i;
        }
        int t=top;
        for(int i=n-1;i>=1;i--){//上凸包
            while(top>t&&cross(s[top-1],s[top],p[i])<=0) top--;
            s[++top]=p[i];id[top]=i;
        }
        tot=top-1;
    };
    for(int i=1;i<=n;i++)
    {
        cin>>p[i].x>>p[i].y;
    }
    Andrew();
    i64 ans=1;
    if(tot==n)
    {
        cout<<ans<<'\n';
        return 0;
    }
    for(int i=1;i<=tot;i++)
    {
        vis[id[i]]=1;
    }
    for(int i=1;i<top;i++)
    {
        vector<pair<double,int>>vec;
        for(int j=1;j<=n;j++) if(!vis[j])
        {
            double ang=angle(s[i],s[i+1],p[j]);
            vec.push_back({ang,j});
        }
        sort(vec.begin(),vec.end(),[&](const auto &x,const auto &y){
            return x.first>y.first;
        });
        vector<int>stk;
        for(auto x:vec)
        {
            if(stk.empty()) stk.push_back(x.second);
            else
            {
                int now=x.second;
                while(!stk.empty())
                {
                    int lst=stk.back();
                    if(angle(s[i+1],s[i],p[now]) < angle(s[i+1],s[i],p[lst]))
                    {
                        stk.pop_back();
                    }
                    else break;
                }
                stk.push_back(now);
            }
        }
        ans+=stk.size();
    }
    cout<<ans<<"\n";
    return 0; 
}
