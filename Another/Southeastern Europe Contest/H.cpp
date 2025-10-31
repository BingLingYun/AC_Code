#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef pair<int,int> pii;

void solve()
{
    int n,m;cin>>n>>m;
    vector a(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    int ans=0;
    for(int j=1;j<m;j++)
    {
        vector<int>b(n+1),c(n+1);
        for(int i=1;i<=n;i++) b[i]=a[i][j];
        for(int i=1;i<=n;i++) c[i]=a[i][j+1];
        sort(b.begin()+1,b.end());
        sort(c.begin()+1,c.end());
        for(int i=n,k=n;i>=1;i--)
        {
            if(c[i]<b[k])
            {
                ans++;k--;
            }
        }
    }
    cout<<(ans>=n ? "YES" : "NO")<<"\n";
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}