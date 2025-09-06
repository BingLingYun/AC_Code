#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef long long i64;

int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int t;cin>>t;
    while(t--)
    {
        int n,m;cin>>n>>m;
        int g=__gcd(n,m);
        if(g!=1)
        {
            cout<<"No"<<"\n";
        }
        else
        {
            cout<<"Yes"<<"\n";
            for(int i=1;i<=n;i++)
            {
                int ans=i*m+1;
                ans%=(n*m);
                cout<<ans<<" ";
            }
            cout<<"\n";
            for(int i=1;i<=m;i++)
            {
                int ans=i*n+1;
                ans%=(n*m);
                cout<<ans<<" ";
            }
            cout<<"\n";
        }
    }
    return 0;
}