#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(10);
    
    int n;cin>>n;
    map<string,int>mp;
    for(int i=1;i<=n;i++)
    {
        string s;cin>>s;
        mp[s]++;
    }
    for(auto x:mp)
    {
        int val=x.second;
        if(val*2>n)
        {
            cout<<x.first<<"\n";
            return 0;
        }
    }
    cout<<"uh-oh"<<"\n";
    return 0;
}