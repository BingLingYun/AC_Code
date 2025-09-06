//octal
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pdd pair<double, double>
#define pll pair<ll, ll>
#define debug(x) cerr << #x << ": " << x << '\n';
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
inline void solve()
{
    int a, b, c;
    cin >> a >> b >> c;
    cout << 100 << endl;
    for(int i=1; i<=50; i++)
        cout << a << " ";
    for(int i=51; i<=95; i++)
        cout << b << " ";
    for(int i=96; i<=99; i++)
        cout << c << " ";
    cout << c+1 << endl;
}
int main()
{
    cout << fixed << setprecision(10);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t;
    t = 1;
    while(t --)
        solve();
    return 0;
}