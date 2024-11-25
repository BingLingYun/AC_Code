//octal
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pdd pair<double, double>
#define pss pair<string, string>
#define pll pair<ll, ll>
#define debug(x) cerr << #x << ": " << x << '\n';
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
inline void solve()
{
    int n;
    cin >> n;
    vector<string> s(n+1);
    vector<int> a(n+1);
    for(int i=1; i<=n; i++) {
        cin >> s[i] >> a[i];
    }
    // 上N 下S 左W 右E
    int x = 0, y = 0;
    vector<pair<string, int>> res;
    res.push_back({s[1], 0});
    res.push_back({"Z", a[1]});
    map<pss, string> to;
    to[{"N", "W"}] = "L";
    to[{"N", "E"}] = "R";
    to[{"S", "W"}] = "R";
    to[{"S", "E"}] = "L";

    to[{"W", "N"}] = "R";
    to[{"E", "N"}] = "L";
    to[{"W", "S"}] = "L";
    to[{"E", "S"}] = "R";
    string lst = s[1];
    for(int i=2; i<=n; i++) {
        res.push_back({to[{lst, s[i]}], 0});
        res.push_back({"Z", a[i]});
        lst = s[i];
    }
    int m = res.size() - 1;
    cout << m << " ";
    for(auto [d, y]: res) {
        cout << d << " ";
        if(y != 0) cout << y;
        cout << endl;
    }
}
int main()
{
    cout << fixed << setprecision(10);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    while(t --)
        solve();
    return 0;
}