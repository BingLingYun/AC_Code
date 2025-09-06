#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

void solve()
{
    int n;cin>>n;
    vector<int>a(5),t(6),c(5);
    for(int i=1;i<=n;i++)
    {
        string s;cin>>s;
        int op;
        if(s[1]=='D') op=1;
        else if(s[1]=='C') op=2;
        else if(s[1]=='H') op=3;
        else if(s[1]=='S') op=4;
        a[op]+=1;
    }
    for(int i=0;i<6;i++) cin>>t[i];
    auto get = [&] (int x,int y)
    {
        i64 val=x*(1<<6)+y;
        return val;
    };
    unordered_map<i64,int>mp;
    int now=0,sta=0;
    int base=0;
    for(int i=1;i<=4;i++)
    {
        if(a[i]%5==0 && a[i]) base+=a[i]/5-1,a[i]=5;
        else base+=a[i]/5,a[i]%=5;
    }
    for(int i=1;i<=4;i++)
    {
        now=now*52+a[i];
    }
    for(int i=5;i>=0;i--)
    {
        sta*=2;sta+=t[i];
    }
    function<int(int,int)> dfs = [&] (int num,int sta)
    {
        if(mp.count(get(num,sta))) return mp[get(num,sta)];
        int x=num;
        for(int i=4;i>=1;i--)
        {
            c[i]=x%52;x/=52;
        }
        c[0]=x;

        if(sta==0)
        {
            int ans=0;
            for(int i=1;i<=4;i++) ans+=c[i]/5,c[i]%=5;
            for(int i=1;i<=4;i++)
            {
                if(c[i]==4 && c[0]>=1)
                {
                    ans+=1;c[i]=0;c[0]-=1;
                }
            }
            for(int i=1;i<=4;i++)
            {
                if(c[i]==3 && c[0]>=2)
                {
                    ans+=1;c[i]=0;c[0]-=2;
                }
            }
            return mp[get(num,sta)]=ans;
        }

        int mx=0;
        auto d=c;
        auto change = [&] ()
        {
            int now=0;
            for(int j=0;j<=4;j++) now=now*52+d[j];
            return now;
        };
        for(int i=0;i<4;i++)
        {
            if((sta>>i&1) ==0 ) continue;
            int H=sta^(1<<i);
            mx=max(mx,dfs(num,H));
            for(int j=0;j<=4;j++)
            {
                d[j]-=1;d[i+1]+=1;
                if(d[j]>=0)
                {
                    int C=change();
                    mx=max(mx,dfs(C,H));
                }
                d[j]+=1;d[i+1]-=1;
            }
            for(int j=0;j<=4;j++)
            {
                for(int k=0;k<=4;k++)
                {
                    d[j]-=1;d[k]-=1;d[i+1]+=2;
                    if(d[j]>=0 && d[k]>=0)
                    {
                        int C=change();
                        mx=max(mx,dfs(C,H));
                    }
                    d[j]+=1;d[k]+=1;d[i+1]-=2;
                }
            }
            for(int j=0;j<=4;j++)
            {
                for(int k=0;k<=4;k++)
                {
                    for(int l=0;l<=4;l++)
                    {
                        d[j]-=1;d[k]-=1;d[l]-=1;d[i+1]+=3;
                        if(d[j]>=0 && d[k]>=0 && d[l]>=0)
                        {
                            int C=change();
                            mx=max(mx,dfs(C,H));
                        }
                        d[j]+=1;d[k]+=1;d[l]+=1;d[i+1]-=3;
                    }
                }
            }
        }
        if(sta>>4&1)
        {
            int H=sta^(1<<4);
            for(int j=0;j<=4;j++)
            {
                if(d[j]<1) continue;
                d[j]-=1;d[0]+=1;
                int C=change();
                mx=max(mx,dfs(C,H));
                d[j]+=1;d[0]-=1;
            }
        }
        if(sta>>5&1)
        {
            int H=sta^(1<<5);
            for(int j=0;j<=4;j++)
            {
                for(int k=0;k<=4;k++)
                {
                    if(d[j]>0 && d[k]>0)
                    {
                        d[j]+=1;d[k]-=1;
                        int C=change();
                        mx=max(mx,dfs(C,H));
                        d[j]-=1;d[k]+=1;
                    }
                }
            }
        }
        return mp[get(num,sta)]=mx;
    };
    int ans=dfs(now,sta)+base;
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}