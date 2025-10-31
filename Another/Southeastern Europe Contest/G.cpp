#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    int n;cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    map<int,int>cnt,mx;
    vector<int>id(n+1);
    for(int i=1;i<=n;i++)
    {
        cnt[a[i]]++;
        id[i]=cnt[a[i]];
    }
    vector<int>dp(n+1),pre(n+1);
    for(int i=1;i<=n;i++)
    {
        if(id[i]==1)
        {
            dp[i]=pre[i]+1;
            pre[i]=pre[i-1];
        }
        else
        {
            int now = mx[a[i]]+id[i]+1;
            dp[i]=now;
            pre[i]=max(pre[i-1],dp[i]);
        }
        if(mx.find(a[i]) != mx.end()) mx[a[i]]=max(mx[a[i]],pre[i-1]-id[i]);
        else mx[a[i]]=pre[i-1]-id[i];
    }
    cout<<pre[n]<<"\n";
    return 0;
}