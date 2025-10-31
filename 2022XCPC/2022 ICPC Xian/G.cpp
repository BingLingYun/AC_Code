#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int n;cin>>n;
    vector<string>s(n+1);
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
    }
    sort(s.begin()+1,s.end(),[&](auto x,auto y){
        return x.size()<y.size();
    });

    if(s[1].size()!=1)
    {
        cout<<0<<"\n";
        return 0;
    }
    int ans=1;
    map<string,int>vis;
    for(int i=1;i<=n;i++)
    {
        if(s[i].size()==1) vis[s[i]]=1;
        else
        {
            string a="",b="";
            for(int j=0;j<s[i].size()-1;j++) a+=s[i][j];
            for(int j=1;j<s[i].size();j++) b+=s[i][j];
            if(vis[a] && vis[b]) vis[s[i]]=1,ans=max(ans,(int)s[i].size());
        }
    }
    cout<<ans<<"\n";
    return 0;
}