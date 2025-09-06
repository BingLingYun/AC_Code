#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef long long i64;

void solve()
{
    int n,f;cin>>n>>f;
    vector<array<int,3>>line(n+1);
    vector<pii>a(n+1);
    for(int i=1;i<=n;i++)
    {
        int x,y;cin>>x>>y;
        a[i]={x,y};
        line[i]={x,y,i};
    }
    sort(line.begin()+1,line.end());

    vector<vector<int>>vec(n+1);
    vector<int>L(n+1),R(n+1);
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        auto [l,r,id]=line[i];
        if(l<=R[cnt])
        {
            vec[cnt].push_back(id);
            R[cnt]=max(R[cnt],r);
        }
        else
        {
            ++cnt;
            L[cnt]=l,R[cnt]=r;
            vec[cnt].push_back(id);
        }
    }
    vector<int>p;
    if(f > R[cnt])
    {
        sort(line.begin()+1,line.end(),[&](auto x,auto y){
            return x[1]>y[1];
        });
        for(int i=1;i<=n;i++) p.push_back(line[i][2]);
    }
    else 
    {
        int pos=0;
        for(int i=1;i<=cnt;i++)
        {
            if(L[i]<=f && R[i]>=f)
            {
                pos=i;break;
            }
        }
        for(int i=2;i<=cnt;i++)
        {
            if(L[i]>f && R[i-1]<f)
            {
                pos=i;
                break;
            }
        }
        if(!pos)
        {
            pos=1;
        }
        vector<int>vis(n+1);
        int C=0;
        for(int i=pos;i<=cnt;i++)
        {
            for(auto x:vec[i])
            {
                auto [l,r]=a[x];
                if(r>C)
                {
                    C=r;
                    vis[x]=1;
                    p.push_back(x);
                }
            }
        }
        sort(line.begin()+1,line.end(),[&](auto x,auto y){
            return x[1]>y[1];
        });
        for(int i=1;i<=n;i++)
        {
            auto [l,r,id]=line[i];
            if(vis[id]) continue;
            p.push_back(id);
        }
    }
    i64 ans=0;
    for(auto x:p)
    {
        auto [l,r]=a[x];
        ans+=max(0,l-f);
        ans+=r-l;
        f=r;
    }
    cout<<ans<<"\n";
    for(auto x:p) cout<<x<<" ";cout<<"\n";
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