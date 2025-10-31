#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int n,c1,c2;cin>>n>>c1>>c2;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        string s;cin>>s;
        int op=0;
        if(s[0]==s[1]==s[2]) op=2;
        else if(s[0]==s[1] || s[0]==s[2] || s[1]==s[2]) op=1;
        else op=0;
        int res=0;
        if(op==0)
        {
            res=3*min(c1,c2);
        }
        else if(op==1)
        {
            res+=min(c1,c2);
            res+=min(c1*2,c2);
        }
        else
        {
            res+=min({3*c1,3*c2,c1+c2});
        }
        ans+=res;
    }
    cout<<ans<<"\n";
    return 0;
}