#include <bits/stdc++.h>

#define i64 long long
#define pii pair<int, int>
#define pll pair<i64, i64>
#define int128 __int128_t
#define ull unsigned long long
#define debug(x) cout << "# " << x << "\n"
using namespace std;

constexpr i64 mod = 998244353;

i64 exgcd(i64 a,i64 b,i64 &x,i64 &y)
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    i64 xx,yy;
    i64 Gcd=exgcd(b,a%b,xx,yy);
    x=yy;
    y=xx-(a/b)*yy;
    return Gcd;
}

i64 cal(i64 a,i64 b,i64 c)
{
    i64 x,y;
    i64 gcd=exgcd(a,b,x,y);
    if(c%gcd) return -1;
    b/=gcd;if(b<0) b=-b;
    x=x*(c/gcd)%b;
    if(x<0) x+=b;
    return x;
}
void solve()
{
    int a,b;cin>>a>>b;
    auto clr = [&] (int x)
    {
        while(x%2==0) x/=2;
        while(x%5==0) x/=5;
        return x;
    };
    i64 C=1e9,D=1e9;
    int w=clr(b);
    for(i64 i=0,two=1;i<=30,two<=1e9;i++,two*=2)
    {
        for(i64 j=0,five=1;j<=30,five*two<=1e9;j++,five*=5)
        {
            i64 d=two*five*w;
            if(d>1e9) break;
            //ad+bc=k*w*w
            // (b/w)c - k*w= (d/w)*a
            i64 mn=cal(1ll*b/w,-w,-1ll*a*d/w);
            if(mn<C) C=mn,D=d;
        }
    }
    cout<<C<<" "<<D<<"\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
/*
4
1 2
2 3
3 7
19 79
*/
