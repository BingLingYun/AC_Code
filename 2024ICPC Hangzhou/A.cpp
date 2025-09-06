#include<bits/stdc++.h>

using namespace std;

void solve()
{
    string a,b,c;cin>>a>>b>>c;
    if(a.size()!=b.size())
    {
        cout<<"NO"<<"\n";
        return;
    }
    if(a.size()!=c.size())
    {
        cout<<"YES"<<"\n";
        return;
    }
    vector<int>f(26);iota(f.begin(),f.end(),0);
    int n=a.size();
    function<int(int)> find = [&] (int x)
    {
        return (f[x]==x ? x : f[x]=find(f[x]));
    };
    for(int i=0;i<n;i++)
    {
        int x=a[i]-'a',y=b[i]-'a';
        int fx=find(x),fy=find(y);
        if(fx!=fy)
        {
            f[fx]=fy;
        }
    }
    for(int i=0;i<n;i++)
    {
        int x=a[i]-'a',y=c[i]-'a';
        int fx=find(x),fy=find(y);
        if(fx!=fy)
        {
            cout<<"YES"<<"\n";
            return;
        }
    }
    cout<<"NO"<<"\n";
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