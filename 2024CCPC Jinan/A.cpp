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
    cout<<fixed<<setprecision(15);

    int n,m,k;cin>>n>>m>>k;
    map<string,int>mp;
    vector<vector<string>>vec(n+1,vector<string>(m+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            string s="";
            for(int c=1;c<=k;c++)
            {
                char ch;cin>>ch;
                s+=ch;
            }
            vec[i][j]=s;
            mp[s]+=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(mp[vec[i][j]]==1)
            {
                cout<<i<<" "<<j<<"\n";
                return 0;
            }
        }
    }
    return 0; 
}