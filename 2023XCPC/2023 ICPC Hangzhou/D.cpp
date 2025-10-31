#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

void solve()
{
    int n;cin>>n;
    if(n==2)
    {
        cout<<"1 -3 -3 1"<<"\n";
    }
    else if(n==3)
    {
        cout<<"1 -10 6 6 -10 1"<<"\n";
    }
    else
    {
        cout<<1<<" ";
        for(int i=1;i<=n-1;i++) cout<<"2 -1"<<" ";
        cout<<3-n<<" ";
        cout<<"\n";
    }
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);
    cout<<fixed<<setprecision(15);

    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}