#include<bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int,int> pii;

//求最大流
template<class T>
struct MaxFlow {
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };
    int n;
    std::vector<_Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    MaxFlow() {}
    MaxFlow(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
    std::vector<bool> minCut() {
        std::vector<bool> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = (h[i] != -1);
        }
        return c;
    }
    struct Edge {
        int from;
        int to;
        T cap;
        T flow;
    };
    std::vector<Edge> edges() {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};
void solve()
{
    int n,m;cin>>n>>m;
    MaxFlow<int>g(2*n+2);
    for(int i=1;i<=n;i++)
    {
        g.addEdge(0,i,1);
    }
    for(int i=1;i<=n;i++)
    {
        g.addEdge(i+n,2*n+1,1);
    }
    for(int i=1;i<=m;i++)
    {
        int u,v;cin>>u>>v;
        v+=n;
        g.addEdge(u,v,1);
    }
    g.flow(0,2*n+1);

    auto Edge = g.edges();
    
    vector<vector<pii>>e(2*n+2);
    for(auto [from,to,cap,flow]:Edge)
    {
        e[from].push_back({to,cap-flow});
        e[to].push_back({from,flow});
    }
    vector<int>ans(2),vis(2*n+2);
    function<void(int,int)> dfs = [&] (int u,int op)
    {
        ans[op]+=op?(u<=n):(u>n);
        vis[u]=1;
        for(auto [v,w]:e[u])
        {
            if(vis[v] || w!=op) continue;
            dfs(v,op);
        }
    };
    dfs(0,1);dfs(2*n+1,0);
    cout<<1ll*(ans[0]-1)*(ans[1]-1)<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}