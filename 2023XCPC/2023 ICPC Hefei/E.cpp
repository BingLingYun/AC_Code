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
    
    int n,m;cin>>n>>m;
    vector<vector<int>>a(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
    vector<vector<int>>vec(2*n*m+1);
    map<int,pii>mp;
    int tot=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!mp.count(a[i][j])) 
            {
                mp[a[i][j]]={tot+1,tot+2};
                tot+=2;
            }
            auto [id1,id2]=mp[a[i][j]];
            vec[id1].push_back(i);
            vec[id2].push_back(j);
        }
    }
    
    i64 ans=0;
    for(int i=1;i<=tot;i++)
    {
        sort(vec[i].begin(),vec[i].end());
        i64 sum=0;
        for(int j=0;j<vec[i].size();j++)
        {
            i64 res=1ll*j*vec[i][j]-sum;
            ans+=res;
            sum+=vec[i][j];
        }
    }
    cout<<ans*2<<"\n";
    return 0;
}