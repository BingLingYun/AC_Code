#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef long long i64;

void solve()
{
    int n,k;cin>>n>>k;
    vector<int>p(n+1),siz(n+1),tag(n+1);
    vector<pii>vec(k+1);
    for(int i=1;i<=k;i++)
    {
        int l,r;cin>>l>>r;
        for(int j=r;j>l;j--)
        {
            p[j]=j-1;
        }
        for(int j=l;j<=r;j++)
        {
            siz[j]=(r-l+1)-(j-l);
        }
        vec[i]={r-l+1,l};
    }
    sort(vec.begin()+1,vec.end(),[&](auto x,auto y){
        return x.first<y.first;
    });
    int now=vec[k].first+vec[k].second-1;
    for(int i=1;i<k;i++)
    {
        auto [len,id]=vec[i];
        while(siz[now]<len && p[now])
        {
            siz[p[now]]+=tag[now];
            tag[p[now]]+=tag[now];
            now=p[now];
        }
        if(p[now]==0)
        {
            cout<<"IMPOSSIBLE"<<"\n";
            return;
        }
        siz[p[now]]+=len;
        tag[p[now]]+=len;
        p[id]=p[now];
    }
    for(int i=1;i<=n;i++) cout<<p[i]<<" ";
    cout<<"\n";
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