#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
#define all(x) x.begin(),x.end()
using namespace std;

constexpr i64 mod=998244353;


int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout<<fixed<<setprecision(15);

    int n;cin>>n;
    vector<array<int,4>>vec(n+1);
    for(int i=1;i<=n;i++)
    {
        string s;cin>>s;
        if(s[0]=='P')
        {
            int val;string t;
            cin>>val;vec[i][0]=val;
            cin>>t;cin>>t;t.pop_back();
            val=0; for(int j=0;j<t.size();j++) val=val*10+(t[j]-'0'); vec[i][1]=val;
            cin>>t;cin>>val;vec[i][2]=val;
            cin>>t;cin>>val;vec[i][3]=val; 
        }   
        else
        {
            vec[i][0]=vec[i][1]=0;
            int val;string t;
            cin>>t>>val;vec[i][2]=val;
            cin>>t>>val;vec[i][3]=val;
        }
    }

    //f[u][a]=(cnt,v),表示当前栈顶为a,去执行u指令时，需要执行cnt条指令把a pop掉，并且去执行v指令
    vector<vector<pll>>f(1025,vector<pll>(1025,{-1,-1}));
    set<pll>st;
    function<pll(int,int)> dfs = [&] (int u,int a)
    {
        if(f[u][a].first!=-1) return f[u][a];
        if(st.find({u,a})!=st.end())
        {
            cout<<-1<<"\n";exit(0);
        }
        if(a==0 && vec[u][0]==0)
        {
            return f[u][a]=make_pair(1,0);
        }
        if(vec[u][0] && vec[u][0]==a)
        {
            return f[u][a]=make_pair(1,vec[u][1]);
        }
        int b=vec[u][2],v=vec[u][3];
        st.insert({u,a});
        auto [cnt1,z1]=dfs(v,b);cnt1%=mod;
        if(z1==0)
        {
            f[u][a]={(cnt1+1)%mod,z1};
        }
        else
        {
            auto [cnt2,z2]=dfs(z1,a);cnt2%=mod;
            f[u][a]={(cnt1+cnt2+1)%mod,z2};
        }
        st.erase({u,a});
        return f[u][a];
    };
    pll ans=dfs(1,0);
    cout<<ans.first<<"\n";
    return 0; 
}