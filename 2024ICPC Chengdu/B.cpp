#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pdd pair<double, double>
#define pll pair<ll, ll>
#define debug(x) cerr << #x << ": " << x << '\n';
#define endl '\n'
typedef long long ll;
typedef long long i64;
typedef unsigned long long ull;

constexpr i64 mod=1e9+7;
i64 dp[2][305][305][3];
i64 g[305][305][305];
inline void solve()
{
    int n,q;cin>>n>>q;
    string s;cin>>s;s=" "+s;
    int lst=0;
    int sum=0;
    if(s[1]=='?')
    {
        dp[lst][1][0][0]=dp[lst][0][1][1]=dp[lst][0][0][2]=1;
        sum++;
    }
    else
    {
        int now=s[1]-'a';
        dp[lst][0][0][now]=1;
    }
    for(int i=2;i<=n;i++)
    {
        int nxt=lst^1;
        if(s[i]=='?')
        {
            sum+=1;
            for(int a=0;a<=sum;a++)
            {
                for(int b=0;a+b<=sum;b++)
                {
                    if(a>=1)
                    {
                        (dp[nxt][a][b][0]+=dp[lst][a-1][b][1]+dp[lst][a-1][b][2])%=mod;
                    }
                    if(b>=1)
                    {
                        (dp[nxt][a][b][1]+=dp[lst][a][b-1][0]+dp[lst][a][b-1][2])%=mod;
                    }
                    int c=sum-a-b;
                    if(c>=1)
                    {
                        (dp[nxt][a][b][2]+=dp[lst][a][b][0]+dp[lst][a][b][1])%=mod;
                    }
                }
            }
        }
        else
        {
            int now=s[i]-'a';
            for(int a=0;a<=sum;a++)
            {
                for(int b=0;a+b<=sum;b++)
                {
                    dp[nxt][a][b][now]=(dp[lst][a][b][0]+dp[lst][a][b][1]+dp[lst][a][b][2]-dp[lst][a][b][now])%mod;
                }
            }
        }

        for(int j=0;j<=300;j++)
        {
            for(int k=0;k<=300;k++)
            {
                for(int sta=0;sta<=2;sta++)
                {
                    dp[lst][j][k][sta]=0;
                }
            }
        }
        lst^=1;
    }
    
    for(int a=0;a<=sum;a++)
    {
        for(int b=0;a+b<=sum;b++)
        {
            int c=sum-a-b;
            for(int sta=0;sta<=2;sta++)
            {
                (g[a][b][c]+=dp[lst][a][b][sta])%=mod;
            }
        }
    }
    vector<vector<i64>>pre(sum+1,vector<i64>(sum+1));
    for(int a=0;a<=sum;a++)
    {
        for(int b=0;a+b<=sum;b++)
        {
            int c=sum-a-b;
            pre[a][b]=(b==0 ? 0 : pre[a][b-1])+g[a][b][c];
            pre[a][b]%=mod;
        }
    }
    while(q--)
    {
        int x,y,z;cin>>x>>y>>z;
        i64 ans=0;
        for(int a=0;a<=min(x,sum);a++)
        {
            int yu=sum-a;
            int l=0;
            if(yu<=z) l=0;
            else l=yu-z;
            int r=yu;
            r=min(r,y);
            if(l<=r)
            {
                (ans+=(pre[a][r]-(l>0 ? pre[a][l-1] : 0)+mod)%mod)%=mod;
            }
        }
        cout<<ans<<"\n";
    }
}
int main()
{
    cout << fixed << setprecision(10);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t;t=1;
    while(t --)
        solve();
    return 0;
}