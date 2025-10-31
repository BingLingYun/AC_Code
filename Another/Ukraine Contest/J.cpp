#include <bits/stdc++.h>
using namespace std;
using ll = long long;

inline void solve()
{
    int n;
    cin >> n;
    vector<int> p(n + 1), pos(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
        pos[p[i]] = i;
    }
    vector<int> fa(n + 1);
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
    function<int(int)> find = [&](int x)
    {
        if (fa[x] != x)
            return fa[x] = find(fa[x]);
        else
            return x;
    };
    for (int i = 1; i <= n; i++)
    {
        int u = i, v = p[i];
        int fu = find(u), fv = find(v);
        fa[fu] = fv;
    }
    set<int> st;
    for (int i = 1; i <= n; i++)
    {
        st.insert(find(i));
    }
    if (st.size() >= 2)
    {
        vector<int> res;
        int t = find(1);
        for (int i = 1; i <= n; i++)
        {
            if (find(i) == t)
                res.push_back(i);
        }
        cout << n << endl;
        cout << res.size() << endl;
        for (int x : res)
        {
            cout << pos[x] << " ";
        }
        cout << endl;
        return;
    }
    cout<<n-2<<"\n";
    vector<int>ans;
    int x=1;
    while(1)
    {
        ans.push_back(x);
        int y=p[x];
        if(y==2) break;
        x=p[x];
    }
    cout<<ans.size()<<"\n";
    for(auto x:ans) cout<<x<<" ";
    cout<<"\n";
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}