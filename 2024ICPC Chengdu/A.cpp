#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pdd pair<double, double>
#define pll pair<ll, ll>
#define debug(x) cerr << #x << ": " << x << '\n';
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
inline void solve()
{
    string s;cin>>s;s=" "+s;
    int n=s.size()-1;
    if(s[n-2]!='>' || s[n-1]!='>' || s[n]!='>' || s[1]=='-')
    {
        cout<<"No"<<"\n";
        return;
    }
    int pos=0;
    for(int i=n;i>=1;i--)
    {
        if(s[i]!='>')
        {
            pos=i;break;
        }
    }
    if(!pos)
    {
        cout<<"No"<<"\n";
        return;
    }
    int h=0;
    vector<pii>ans;
    for(int i=1;i<pos;i++)
    {
        if(s[i]=='>')
        {
            ans.push_back({i,n-i+1});
            h=i;
        }
    }
    if(!h)
    {
        cout<<"No"<<"\n";
        return;
    }
    for(int i=n-1;i>=pos+3;i--)
    {
        ans.push_back({h,i-h+1});
    }
    cout<<"Yes"<<" "<<ans.size()<<"\n";
    for(auto [x,y]:ans) cout<<x<<" "<<y<<"\n";
}
int main()
{
    cout << fixed << setprecision(10);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    while(t --)
        solve();
    return 0;
}