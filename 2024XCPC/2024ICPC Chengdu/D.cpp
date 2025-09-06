#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
#define all(x) x.begin(),x.end()
using namespace std;

constexpr i64 mod=998244353;

struct ST{
    vector<vector<int>>f;
    int n;
    ST(int N)
    {
        f=vector<vector<int>>(N+10,vector<int>(32,0));
        n=N;
    }
    int quiry(int l,int r)
    {
        int ln=(int)(log(r-l+1)/log(2));
        return (min(f[l][ln],f[r-(1<<ln)+1][ln]));
    }
    void build(vector<int>a)
    {
        for(int i=1;i<=n;i++)
        {
            f[i][0]=a[i];
        }
        int len=(int)(log(n)/log(2));
        for(int j=1;j<=len;j++)
        {
            for(int i=1;i<=n-(1<<j)+1;i++)
            {
                f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
            }
        }
    }
};
void solve()
{
    int n,k;cin>>n>>k;
    vector<int>a(n+1),pos(n+1);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];pos[a[i]]=i;
    }
    if(n%2==0)
    {
        if(k>1)
        {
            cout<<-1;
        }
        else
        {
            for(int i=1;i<=n;i++)
            {
                if(a[i]%2==0)
                {
                    cout<<a[i]-1<<" ";
                }
                else cout<<a[i]+1<<" ";
            } 
        }
        cout<<"\n";
    }
    else
    {
        if(k>n-1)
        {
            cout<<-1<<"\n";
            return;
        }
        auto get = [&] (int pos,int op)
        {
            if(op==1)
            {
                if(a[pos]%2==0) return a[pos]-1;
                else return a[pos]+1;
            }
            else
            {
                if(a[pos]%2==0) return a[pos]+1;
                else return a[pos]-1;
            }
        };
        ST st(n);st.build(pos);
        vector<pii>vec,H(n+1);
        for(int i=1;i<n;i+=2)
        {
            vec.push_back({i,1});
            vec.push_back({i,2});
        }
        sort(vec.begin(),vec.end(),[&](const auto &X,const auto &Y){
            int x1=X.first,x2=Y.first;
            set<int>now;
            for(int i=1;i<=3;i++) now.insert(pos[x1+i-1]),now.insert(pos[x2+i-1]);
            if(X.second==1)
            {
                H[pos[x1]].first=x1+2;
                H[pos[x1+1]].first=x1;
                H[pos[x1+2]].first=x1+1;
            }
            else
            {
                H[pos[x1]].first=x1+1;
                H[pos[x1+1]].first=x1+2;
                H[pos[x1+2]].first=x1;
            }
            if(Y.second==1)
            {
                H[pos[x2]].second=x2+2;
                H[pos[x2+1]].second=x2;
                H[pos[x2+2]].second=x2+1;
            }
            else
            {
                H[pos[x2]].second=x2+1;
                H[pos[x2+1]].second=x2+2;
                H[pos[x2+2]].second=x2;
            }
            for(auto x:now)
            {
                if(H[x].first==0)
                {
                    if(a[x]<x1) H[x].first=get(x,1);
                    else H[x].first=get(x,2);
                }
                if(H[x].second==0)
                {
                    if(a[x]<x2) H[x].second=get(x,1);
                    else H[x].second=get(x,2);
                }
            }
            if(min(x1+2,x2+2)+1 <= max(x1,x2)-1)
            {
                int l=min(x1+2,x2+2)+1,r=max(x1,x2)-1;
                int h=st.quiry(l,r);
                now.insert(h);
                if(x1<x2)
                {
                    if(a[h]%2==0) H[h].first=a[h]+1,H[h].second=a[h]-1;
                    else H[h].first=a[h]-1,H[h].second=a[h]+1;
                }
                else
                {
                    if(a[h]%2==0) H[h].first=a[h]-1,H[h].second=a[h]+1;
                    else H[h].first=a[h]+1,H[h].second=a[h]-1;
                }
            }
            int flag=0;
            for(auto x:now)
            {
                if(H[x].first < H[x].second)
                {
                    flag=1;break;
                }
                else if(H[x].first > H[x].second)
                {
                    flag=0;break;
                }
            }
            for(auto x:now) H[x].first=H[x].second=0;
            return flag;
        });
        auto [x,op]=vec[k-1];
        if(op==1)
        {
            H[pos[x]].first=x+2;
            H[pos[x+1]].first=x;
            H[pos[x+2]].first=x+1;
        }
        else
        {
            H[pos[x]].first=x+1;
            H[pos[x+1]].first=x+2;
            H[pos[x+2]].first=x;
        }
        for(int i=1;i<=n;i++)
        {
            if(a[i]<x)
            {
                if(a[i]%2==0) cout<<a[i]-1<<" ";
                else cout<<a[i]+1<<" ";
            }
            else if(a[i]>x+2)
            {
                if(a[i]%2==0) cout<<a[i]+1<<" ";
                else cout<<a[i]-1<<" ";
            }
            else
            {
                cout<<H[i].first<<" ";
            }
        }
        cout<<"\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout<<fixed<<setprecision(15);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}