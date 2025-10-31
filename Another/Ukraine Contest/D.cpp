#include<bits/stdc++.h>

using namespace std;

void solve()
{
    int n;cin>>n;
    string s;cin>>s;s=" "+s;
    int ans=0;
    int len=n+1;
    int flag=0;
    for(int i=1;i<=n;i++)
    {
        int j=i;
        while(j<n && s[j+1]==s[j]) j++;
        if(s[i]=='0')
        {
            if(j-i+1 >= 2) flag=1;
        }
        else
        {
            ans+=j-i+1;
            len=min(len,j-i+1);
        }
        i=j;
    }
    if(s[1]=='1' && s[n]=='1' && !flag)
    {
        cout<<ans+len<<"\n";
    }
    else
    {
        cout<<ans<<"\n";
    }
}
int main()
{
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}