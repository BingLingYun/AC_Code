#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;
constexpr i64 mod=998244353;

void solve()
{
    int n;cin>>n;
    vector<int>cnt1(n),cnt2(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int w=i*j;
            cnt2[w%n]++;
            if(w>=n) cnt1[w/n]++;
        }
    }
    map<pii,vector<int>>f;
    for(int i=0;i<n;i++) f[{cnt1[i],cnt2[i]}].push_back(i);

    vector<int>tar;
    map<char,int>c1,c2;
    set<char>ch;
    auto change = [&] (char ch)
    {
        if(ch>='a' && ch<='z') return (ch-'a');
        else return (ch-'A'+26);
    };
    for(int i=1;i<=n*n;i++)
    {
        string s;cin>>s;
        int len=s.size();
        if(len==1)
        {
            c2[s[0]]++;ch.insert(s[0]);
            tar.push_back(change(s[0]));
        }
        else
        {
            c1[s[0]]++;ch.insert(s[0]);
            c2[s[1]]++;ch.insert(s[1]);
            tar.push_back(change(s[0])*52+change(s[1]));
        }
    }
    sort(tar.begin(),tar.end());
    vector<char>sc[60];
    for(auto x:ch)
    {
        pii c=make_pair(c1[x],c2[x]);
        for(auto p:f[c]) sc[p].push_back(x);
    }
    vector<char>ans(n);
    vector<int>use(256);
    auto check = [&]()
    {
        vector<int>tmp;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                int w=i*j;
                tmp.push_back(w<n ? change(ans[w]) : change(ans[w/n])*52+change(ans[w%n]));
            }
        }
        sort(tmp.begin(),tmp.end());
        return tmp == tar;
    };
    function<int(int)> dfs = [&] (int pos)
    {
        if(pos==n) return check();
        for(auto x:sc[pos])
        {
            if(!use[x])
            {
                use[x]=true;
                ans[pos]=x;
                if(dfs(pos+1)) return true;
                use[x]=false;
            }
        }
        return false;
    };
    dfs(0);
    for(int i=0;i<n;i++) cout<<ans[i];cout<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(10);
    
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;    
}