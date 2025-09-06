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
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> score(n+1, m);
    int now = -1;
    vector<ll> get(m+1);
    set<pii> solve;

    while(q --) {
        int op;
        cin >> op;
        if(op == 1) {
            int x;
            cin >> x;
            now = x;
        } else if(op == 2) {
            int id, x;
            cin >> id >> x;
            if(now != x || solve.count({id, x})) continue;
            get[id] += score[x];
            score[x] --;
            solve.insert({id, x});
        } else {
            int id, x;
            cin >> id >> x;
            if(now != x) continue;
            solve.insert({id, x});
        }
    }
    vector<pll> res;
    for(int i=1; i<=m; i++) {
        res.push_back({get[i], i});
    }
    sort(res.begin(), res.end(), [&](pii a, pii b) {
        if(a.first != b.first)
            return a.first > b.first;
        return a.second < b.second;
    });
    for(auto [x, id]: res) {
        cout << id << " " << x << endl;
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