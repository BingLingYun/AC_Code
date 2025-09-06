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
    
    int l,r;cin>>l>>r;
    int tot=1,root=1;
    vector<vector<pii>>g(101);
    vector<vector<pii>>to(101);
    auto getwei = [&] (int x)
    {
        int cnt=0;
        while(x) cnt++,x>>=1;
        return cnt;
    };
    auto chai = [&] (int x)
    {
        vector<int>c;
        while(x) c.push_back(x%2),x>>=1;
        for(int i=c.size()-1;i>=0;i--) cout<<c[i];
        cout<<"\n";
    };
    int cnt1=getwei(l),cnt2=getwei(r);

    auto get = [&] (int l,int r)
    {
        int now=getwei(l);
        int c1=__builtin_popcount(l),c2=__builtin_popcount(r);
        if(c1==1)
        {

            if(r == (1<<now)-1)
            {
                to[1].push_back({now-1,1});
                return;
            }
            g[1].push_back({++tot,1});
            for(int j=now-2;j>=0;j--)
            {
                int pre=tot;
                int op=r>>j&1;
                if(j==0)
                {
                    if(op) to[pre].push_back({0,1});
                    to[pre].push_back({0,0});
                }
                else
                {
                    if(op)
                    {
                        int flag=0;
                        for(int k=j-1;k>=0;k--)
                        {
                            if((r>>k&1)==0) flag=1;
                        }
                        if(!flag)
                        {
                            to[pre].push_back({j,0});
                            to[pre].push_back({j,1});
                            break;
                        }
                        else
                        {
                            to[pre].push_back({j,0});
                            g[pre].push_back({++tot,1});
                        }
                    }
                    else
                    {
                        g[pre].push_back({++tot,0});
                    }
                }
            }
            return;
        }
        if(c2==now)
        {
            g[1].push_back({++tot,1});
            for(int j=now-2;j>=0;j--)
            {
                int pre=tot;
                int op=l>>j&1;
                if(j==0)
                {
                    if(!op) to[pre].push_back({0,0});
                    to[pre].push_back({0,1});
                }
                else
                {
                    if(op)
                    {
                        int flag=0;
                        for(int k=j-1;k>=0;k--)
                        {
                            if(l>>k&1) flag=1;
                        }
                        if(!flag)
                        {
                            to[pre].push_back({j,1});
                            break;
                        }
                        else
                        {
                            g[pre].push_back({++tot,1});
                        }
                    }
                    else
                    {
                        to[pre].push_back({j,1});
                        g[pre].push_back({++tot,0});
                    }
                }
            }
            return;
        }
        
        int pos=-1;
        for(int j=now-1;j>=0;j--)
        {
            int x=l>>j&1,y=r>>j&1;
            if(x==y)
            {
                int pre=tot;
                if(j==now-1) pre=1;
                if(j==0)
                {
                    to[pre].push_back({0,x});
                }
                else g[pre].push_back({++tot,x});
                root=tot;
            }
            else
            {
                if(j==0)
                {
                    int pre=tot;
                    if(j==now-1) pre=1;
                    to[pre].push_back({0,0});
                    to[pre].push_back({0,1});
                    break;
                }
                pos=j;
                break;
            }
        }
        if(pos!=-1)
        {
            g[root].push_back({++tot,0});
            int lx=l,rx=(1<<now)-1;
            for(int j=pos-1;j>=0;j--)
            {
                int pre=tot;
                int op=lx>>j&1;
                if(j==0)
                {
                    if(!op) to[pre].push_back({0,0});
                    to[pre].push_back({0,1});
                }
                else
                {
                    if(op)
                    {
                        int flag=0;
                        for(int k=j-1;k>=0;k--)
                        {
                            if(lx>>k&1) flag=1;
                        }
                        if(!flag)
                        {
                            to[pre].push_back({j,1});
                            break;
                        }
                        else
                        {
                            g[pre].push_back({++tot,1});
                        }
                    }
                    else
                    {
                        to[pre].push_back({j,1});
                        g[pre].push_back({++tot,0});
                    }
                }
            }

            g[root].push_back({++tot,1});
            lx=1<<(now-1),rx=r;
            for(int j=pos-1;j>=0;j--)
            {
                int pre=tot;
                int op=rx>>j&1;
                if(j==0)
                {
                    if(op) to[pre].push_back({0,1});
                    to[pre].push_back({0,0});
                }
                else
                {
                    if(op)
                    {
                        int flag=0;
                        for(int k=j-1;k>=0;k--)
                        {
                            if((rx>>k&1)==0) flag=1;
                        }
                        if(!flag)
                        {
                            to[pre].push_back({j,0});
                            to[pre].push_back({j,1});
                            break;
                        }
                        else
                        {
                            to[pre].push_back({j,0});
                            g[pre].push_back({++tot,1});
                        }
                    }
                    else
                    {
                        g[pre].push_back({++tot,0});
                    }
                }
            }
        }
    };

    if(cnt1==cnt2)
    {
        get(l,r);
    }
    else
    {
        int lx=l,rx=(1<<cnt1)-1;
        get(lx,rx);
        lx=1<<(cnt2-1),rx=r;
        get(lx,rx);
        for(int i=cnt1+1;i<cnt2;i++)
        {
            to[1].push_back({i-1,1});
        }
    }
    
    int mx=-1;
    for(int i=1;i<=100;i++)
    {
        for(auto [x,y]:to[i])
        {
            mx=max(mx,x);
        }
    }
    map<int,pii>mp;
    for(int j=0;j<=mx;j++)
    {
        ++tot;
        if(j==0)
        {
            mp[j]={tot,tot};
        }
        else
        {
            mp[j]={tot,tot+1};
            tot++;
        }
        if(j>0)
        {
            auto [pre1,pre2]=mp[j-1];
            g[tot-1].push_back({pre1,0});
            if(pre1!=pre2) g[tot-1].push_back({pre2,0});
            g[tot].push_back({pre1,1});
            if(pre1!=pre2) g[tot].push_back({pre2,1});
        }
    }
    for(int i=1;i<=100;i++)
    {
        for(auto [x,y]:to[i])
        {
            auto [c,d]=mp[x];
            g[i].push_back({c,y});
            if(c!=d) g[i].push_back({d,y});
        }
    }
    cout<<tot<<"\n";
    for(int i=1;i<=tot;i++)
    {
        cout<<g[i].size()<<" ";
        for(auto [x,y]:g[i])
        {
            cout<<x<<" "<<y<<" ";
        }
        cout<<"\n";
    }
    return 0; 
}
