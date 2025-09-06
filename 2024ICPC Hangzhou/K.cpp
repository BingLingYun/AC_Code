#include<bits/stdc++.h>

using namespace std;

void solve()
{
    int n,m,k;cin>>n>>m>>k;
    vector<int>p(n*m+1);
    vector<vector<int>>vec(n+1);
    for(int i=1;i<=n*m;i++)
    {
        cin>>p[i];
        int x=(p[i]-1)/m+1;
        vec[x].push_back(i);
    }
    int ans=n*m;
    if(k>=m)
    {
        cout<<m<<"\n";
        return;
    }
    for(int i=1;i<=n;i++)
    {
        int h=vec[i][m-k-1];
        ans=min(ans,max(h,m));
    }
    cout<<ans<<"\n";
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