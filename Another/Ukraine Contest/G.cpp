#include<bits/stdc++.h>
using namespace std;
inline void solve()
{
    int n;
    cin >> n;
    vector<int> p(n+1), t(n+1);
    for(int i=1; i<=n; i++)
        cin >> p[i], t[p[i]] = i;
    // for(int i=1; i<=n; i++) {
    //     cout << t[i] << " ";
    // }
    // cout << endl;
    vector<int> res;
    set<int> st;
    for(int i=1; i<=n; i++) {
        if(t[i] == i) res.push_back(i), st.insert(i);
    }
    queue<int> q;
    for(int i=1; i<=n; i++) {
        if(t[i] != i && p[i] != t[i]) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        auto i = q.front();
        q.pop();
        if(!st.count(t[i]) && !st.count(i)) {
            res.push_back(t[i]);
            res.push_back(i);
            st.insert(t[i]);
            st.insert(i);
            while(!st.count(p[i])) {
                i = p[i];
                res.push_back(i);
                st.insert(i);
            }
        }
    }
    for(int i=1; i<=n; i++) {
        if(t[i] != i) {
            if(!st.count(t[i]) && !st.count(i)) {
                res.push_back(t[i]);
                res.push_back(i);
                st.insert(t[i]);
                st.insert(i);
            }
        }
    }
    for(int i=1; i<=n; i++) {
        if(!st.count(i)) res.push_back(i);
    }
    for(int x: res) {
        cout << x << " ";
    }
    // cout << endl;
    // for(int x: res) {
    //     cout << p[x] << " ";
    // }
    cout << endl;
}
int main()
{
    int t;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}