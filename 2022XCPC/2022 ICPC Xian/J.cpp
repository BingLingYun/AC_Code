#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int n;cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a.begin()+1,a.end());
    int ans=0;
    for(int i=n;i>=n-1;i--)
    {
        ans=max(ans,ans+a[i]);
    }
    cout<<ans<<"\n";
    return 0;
}